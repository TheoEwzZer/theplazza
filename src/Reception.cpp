/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Plazza
*/

#include "Error.hpp"
#include "Kitchen.hpp"
#include "Logger.hpp"
#include "Pizzas/APizza.hpp"
#include "Pizzas/Americana.hpp"
#include "Pizzas/Fantasia.hpp"
#include "Pizzas/IPizza.hpp"
#include "Pizzas/Margarita.hpp"
#include "Pizzas/Regina.hpp"
#include "Process.hpp"
#include "Reception.hpp"
#include <algorithm>
#include <cctype>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using std::back_inserter;
using std::cerr;
using std::cin;
using std::cout;
using std::format;
using std::getline;
using std::make_pair;
using std::make_unique;
using std::mutex;
using std::ofstream;
using std::ranges::transform;
using std::regex;
using std::scoped_lock;
using std::smatch;
using std::sregex_iterator;
using std::string;
using std::tolower;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using enum plazza::PizzaSize;
using enum plazza::PizzaType;

plazza::PizzaType plazza::Reception::getType(const string &type) const
{
    unordered_map<string, PizzaType> typeMap = {
        {"regina", REGINA},
        {"margarita", MARGARITA},
        {"americana", AMERICANA},
        {"fantasia", FANTASIA}
    };
    string lowerType;

    for (const auto &c : type) {
        lowerType.push_back(static_cast<char>(::tolower(static_cast<int>(c))));
    }
    if (typeMap.contains(lowerType)) {
        return typeMap[lowerType];
    }
    throw InvalidArgument("Invalid pizza type");
}

plazza::PizzaSize plazza::Reception::getSize(const string &size) const
{
    unordered_map<string, PizzaSize> sizeMap = {
        {"S", S},
        {"M", M},
        {"L", L},
        {"XL", XL},
        {"XXL", XXL}
    };

    if (sizeMap.contains(size)) {
        return sizeMap[size];
    }
    throw InvalidArgument("Invalid pizza size");
}

void plazza::Reception::addPizza(
    const PizzaType type, const PizzaSize size, const int quantity
)
{
    const ScopedLock lock(mMutex);
    for (int i = 0; i < quantity; i++) {
        if (type == REGINA) {
            mPizzas.push(make_unique<Regina>(size));
        } else if (type == MARGARITA) {
            mPizzas.push(make_unique<Margarita>(size));
        } else if (type == AMERICANA) {
            mPizzas.push(make_unique<Americana>(size));
        } else if (type == FANTASIA) {
            mPizzas.push(make_unique<Fantasia>(size));
        }
    }
}

void plazza::Reception::processOrder(const string &order)
{
    const regex orderPattern("([a-zA-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)");
    const sregex_iterator begin(order.begin(), order.end(), orderPattern);
    const sregex_iterator end;
    int quantity = 0;

    if (begin != end) {
        for (sregex_iterator i = begin; i != end; i++) {
            const smatch match = *i;
            const PizzaType type = getType(match[1].str());
            const PizzaSize size = getSize(match[2].str());
            quantity = stoi(match[3].str());
            addPizza(type, size, quantity);
        }
    } else {
        cerr << "Invalid order. Please try again.\n";
    }
}

unique_ptr<plazza::IPipe> plazza::Reception::createPipe(
    const string &pipeName, const bool isInPipe
)
{
    unique_ptr<plazza::IPipe> pipePtr = nullptr;

    if (isInPipe) {
        pipePtr = make_unique<plazza::PipeIn>(pipeName);
    } else {
        pipePtr = make_unique<plazza::PipeOut>(pipeName);
    }
    return pipePtr;
}

pair<plazza::PipeIn *, plazza::PipeOut *> plazza::Reception::createKitchen()
{
    Mutex mutex;
    ScopedLock locker(mutex);
    string pipeIn = format("/tmp/kitchenIn-{}", mKitchenNumber);
    string pipeOut = format("/tmp/kitchenOut-{}", mKitchenNumber);

    auto kitchen = make_unique<Kitchen>(
        pipeIn, pipeOut, mMultiplier, static_cast<size_t>(mCooks),
        static_cast<size_t>(mTime), mLogger.get()
    );
    new Process(*kitchen);
    unique_ptr<plazza::IPipe> pipeInPtr = createPipe(pipeIn, true);
    unique_ptr<plazza::IPipe> pipeOutPtr = createPipe(pipeOut, false);
    mKitchens.push_back(make_pair(
        dynamic_cast<PipeIn*>(pipeInPtr.release()),
        dynamic_cast<PipeOut*>(pipeOutPtr.release())
    ));
    mKitchenNumber++;
    return mKitchens.back();
}

void plazza::Reception::iterateKitchens(IPizza *pizza)
{
    string nbAvailableCooks = "";
    string canCookStr = "";
    list<pair<PipeIn *, PipeOut *>> freeCooks;
    PipeOut *kitchenOut = nullptr;

    auto it = mKitchens.begin();
    while (it != mKitchens.end()) {
        PipeIn *const pipeIn = it->first;
        PipeOut *const pipeOut = it->second;
        pipeOut->write("getAvailableCooks");
        pipeIn->read(nbAvailableCooks);
        if (nbAvailableCooks == "closed") {
            delete pipeIn;
            delete pipeOut;
            it = mKitchens.erase(it);
            continue;
        }
        pipeOut->write(format("canCook-{}", pizza->pack()));
        pipeIn->read(canCookStr);
        bool canCook = canCookStr == "yes";
        if (canCook && (canCookStr != "closed") && (nbAvailableCooks != "0")) {
            freeCooks.push_back(make_pair(pipeIn, pipeOut));
        } else if (nbAvailableCooks == "closed") {
            delete pipeIn;
            delete pipeOut;
            it = mKitchens.erase(it);
            continue;
        }
        it++;
    }
    kitchenOut = ((!mKitchens.empty()) && (!freeCooks.empty())) ?
        freeCooks.front().second : createKitchen().second;
    kitchenOut->write(format("cook-{}", pizza->pack()));
}

void plazza::Reception::startPlazza()
{
    string input;
    unique_ptr<plazza::IPizza> currentPizza;

    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input == "exit") {
            break;
        }
        if (input == "status") {
            for (const auto &[pipeIn, pipeOut] : mKitchens) {
                pipeOut->write("status");
            }
            continue;
        }
        processOrder(input);
        if (mPizzas.empty()) {
            continue;
        }
        if (mKitchens.empty()) {
            createKitchen();
        }
        while (!mPizzas.empty()) {
            if (!mPizzas.tryPop(currentPizza)) {
                continue;
            }
            iterateKitchens(currentPizza.get());
        }
    }
}
