/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Kitchen
*/

#include "Cooks.hpp"
#include "Error.hpp"
#include "Kitchen.hpp"
#include "ScopedLock.hpp"

using std::to_string;
using std::cerr;

plazza::Kitchen::Kitchen(
    const string &pathIn, const string &pathOut,
    const double multiplier, const size_t cooks,
    const size_t time, Logger *logger
) : mMultiplier(multiplier), mCooksMaxNumber(cooks),
    mTime(time), mPathIn(pathOut), mPathOut(pathIn), mLogger(logger)
{
    mCook = make_unique<ThreadPool>(cooks, logger);
    mCommandMap["getAvailableCooks"] = &Kitchen::getAvailableCooks;
    mCommandMap["closed"] = &Kitchen::close;
    mCommandMap["canCook"] = &Kitchen::canCook;
    mCommandMap["status"] = &Kitchen::status;
    mCommandMap["cook"] = &Kitchen::cook;
}

void plazza::Kitchen::getAvailableCooks(const string &arg)
{
    (void)arg;
    const size_t availableCooks = mCook->getCooksAvailable();

    mPipeOut->write(to_string(availableCooks));
}

void plazza::Kitchen::checkClose()
{
    Mutex mutex;
    const ScopedLock locker(mutex);

    auto start = steady_clock::now();
    while (mIsAlive) {
        if (mPizzas.empty()) {
            if (((steady_clock::now() - start) > seconds(5))
            && (mCooksMaxNumber == mCook->getCooksAvailable())) {
                mIsAlive = false;
                mLogger->log(
                    "KITCHEN: The kitchen is closing due to inactivity"
                );
            }
        } else {
            start = steady_clock::now();
        }
        std::this_thread::sleep_for(seconds(1));
    }
}

void plazza::Kitchen::addPizza(unique_ptr<IPizza> pizza)
{
    Mutex mutex;
    const ScopedLock locker(mutex);

    mPizzas.push(move(pizza));
    mCondition.notifyOne();
}

string plazza::Kitchen::ingredientToString(const PizzaIngredient size) const
{
    unordered_map<PizzaIngredient, string> ingredientMap = {
        {CHIEF_LOVE, "Chief love"},
        {DOUGH, "Dough"},
        {EGGPLANT, "Eggplant"},
        {GOAT_CHEESE, "Goat cheese"},
        {GRUYERE, "Gruyere"},
        {HAM, "Ham"},
        {MUSHROOMS, "Mushrooms"},
        {STEAK, "Steak"},
        {TOMATO, "Tomato"},
    };

    if (ingredientMap.contains(size)) {
        return ingredientMap[size];
    }
    throw InvalidArgument("Invalid ingredient");
}

void plazza::Kitchen::refreshFrigo()
{
    while (mIsAlive) {
        std::this_thread::sleep_for(milliseconds(mTime));
        if (!mIsAlive) {
            return;
        }
        Mutex mutex;
        const ScopedLock locker(mutex);
        for (auto &[ingredient, count] : mFrigo) {
            count += 1;
        }
        mLogger->log("KITCHEN: Frigo has been refreshed");
    }
}

bool plazza::Kitchen::isKitchenAlive() const
{
    return mIsAlive;
}

void plazza::Kitchen::cook()
{
    Mutex mutex;
    string order;

    mutex.lock();
    mPipeOut = new PipeOut(mPathOut);
    mutex.unlock();
    mutex.lock();
    mPipeIn = new PipeIn(mPathIn);
    mutex.unlock();
    Thread isAlive;
    isAlive.start([](void *const arg) -> void * {
        auto *const kitchen = static_cast<Kitchen *>(arg);
        kitchen->checkClose();
        return nullptr;
    }, this);
    Thread frigo;
    frigo.start([](void *const arg) -> void * {
        auto *const kitchen = static_cast<Kitchen *>(arg);
        kitchen->refreshFrigo();
        return nullptr;
    }, this);
    while (true) {
        mPipeIn->read(order);
        handleOrder(order);
    }
}

void plazza::Kitchen::handleOrder(string &order)
{
    Mutex mutex;
    const ScopedLock locker(mutex);
    string command = "";
    string argument = "";

    if (!mIsAlive) {
        order = "closed";
    }
    const size_t spacePos = order.find('-');
    if (spacePos != std::string::npos) {
        command = order.substr(0, spacePos);
        argument = order.substr(spacePos + 1);
    } else {
        command = order;
    }

    const auto it = mCommandMap.find(command);
    if (it != mCommandMap.end()) {
        (this->*(it->second))(argument);
    }
}

void plazza::Kitchen::close(const string &arg)
{
    (void)arg;
    mLogger->log("KITCHEN: Closing kitchen");
    mPipeOut->write("closed");
    ::exit(0);
}

void plazza::Kitchen::status(const string &arg)
{
    (void)arg;
    cout << "Kitchen status\n";
    for (const auto &[ingredient, count] : mFrigo) {
        cout << ingredientToString(ingredient) << ": " << count << "\n";
    }
}

void plazza::Kitchen::canCook(const string &arg)
{
    const size_t dashPos = arg.find('-');
    string type;
    string size;
    bool canCook = true;
    const IPizza *const pizza = APizza::unpack(arg);

    if (dashPos == string::npos) {
        throw InvalidArgument("Invalid argument format: " + arg);
    }
    type = arg.substr(0, dashPos);
    size = arg.substr(dashPos + 1);
    const vector<PizzaIngredient> getIngredients = pizza->getIngredients();
    map<PizzaIngredient, size_t> tmpFrigo = mFrigo;
    for (const auto &ingredient : getIngredients) {
        if (tmpFrigo[ingredient] == 0) {
            canCook = false;
            break;
        }
        tmpFrigo[ingredient] -= 1;
    }
    if (canCook) {
        mPipeOut->write("yes");
    } else {
        mPipeOut->write("no");
    }
}

void plazza::Kitchen::cook(const string &arg)
{
    const size_t dashPos = arg.find('-');
    string type;
    string size;
    IPizza *const pizza = APizza::unpack(arg);

    if (dashPos == string::npos) {
        throw InvalidArgument("Invalid argument format: " + arg);
    }
    type = arg.substr(0, dashPos);
    size = arg.substr(dashPos + 1);
    const vector<PizzaIngredient> getIngredients = pizza->getIngredients();
    for (const auto &ingredient : getIngredients) {
        mFrigo[ingredient] -= 1;
    }
    mLogger->log("KITCHEN: Cooking " + type + " " + size);
    mCook->add(new Cooks(pizza, mMultiplier));
    mCook->exec();
}
