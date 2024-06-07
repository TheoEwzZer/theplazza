/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** APizza
*/

#include "../Error.hpp"
#include "APizza.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"
#include "IPizza.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include <format>
#include <iostream>

using enum plazza::PizzaSize;
using enum plazza::PizzaType;
using std::cerr;
using std::format;
using std::make_unique;

plazza::PizzaType plazza::APizza::getType() const
{
    return mType;
}

plazza::PizzaSize plazza::APizza::getSize() const
{
    return mSize;
}

int plazza::APizza::getCookTime() const
{
    return mBakTime;
}

std::vector<plazza::PizzaIngredient> plazza::APizza::getIngredients() const
{
    return mIngredients;
}

string plazza::APizza::getTypeString() const
{
    unordered_map<PizzaType, string> typeMap = {
        {REGINA, "Regina"},
        {MARGARITA, "Margarita"},
        {AMERICANA, "Americana"},
        {FANTASIA, "Fantasia"}
    };

    if (typeMap.contains(mType)) {
        return typeMap[mType];
    }
    throw InvalidArgument("Invalid pizza type");
}

string plazza::APizza::getSizeString() const
{
    unordered_map<PizzaSize, string> sizeMap = {
        {S, "S"},
        {M, "M"},
        {L, "L"},
        {XL, "XL"},
        {XXL, "XXL"}
    };

    if (sizeMap.contains(mSize)) {
        return sizeMap[mSize];
    }
    throw InvalidArgument("Invalid pizza size");
}

plazza::PizzaType plazza::APizza::getTypeByString(const string &type) const
{
    unordered_map<string, PizzaType> typeMap = {
        {"Regina", REGINA},
        {"Margarita", MARGARITA},
        {"Americana", AMERICANA},
        {"Fantasia", FANTASIA}
    };

    if (typeMap.contains(type)) {
        return typeMap[type];
    }
    throw InvalidArgument("Invalid pizza type");
}

plazza::PizzaSize plazza::APizza::getSizeByString(const string &size)
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

string plazza::APizza::pack() const
{
    return format("{}-{}", getTypeString(), getSizeString());
}

plazza::IPizza *plazza::APizza::unpack(const string &data)
{
    string type;
    string size;
    const size_t dashPos = data.find('-');

    if (dashPos == string::npos) {
        throw InvalidArgument("Invalid argument format: " + data);
    }
    type = data.substr(0, dashPos);
    size = data.substr(dashPos + 1);
    if (type == "Regina") {
        return new Regina(getSizeByString(size));
    }
    if (type == "Margarita") {
        return new Margarita(getSizeByString(size));
    }
    if (type == "Americana") {
        return new Americana(getSizeByString(size));
    }
    if (type == "Fantasia") {
        return new Fantasia(getSizeByString(size));
    }
    throw InvalidArgument("Invalid pizza type");
}

ostream &operator<<(ostream &os, const plazza::PizzaType &type)
{
    using enum plazza::PizzaType;
    switch (type) {
        case REGINA:
            os << "Regina";
            break;
        case MARGARITA:
            os << "Margarita";
            break;
        case AMERICANA:
            os << "Americana";
            break;
        case FANTASIA:
            os << "Fantasia";
            break;
        default:
            os << "Invalid size";
            break;
    }
    return os;
}

ostream &operator<<(ostream &os, const plazza::PizzaSize &size)
{
    using enum plazza::PizzaSize;
    switch (size) {
        case S:
            os << "S";
            break;
        case M:
            os << "M";
            break;
        case L:
            os << "L";
            break;
        case XL:
            os << "XL";
            break;
        case XXL:
            os << "XXL";
            break;
        default:
            os << "Invalid size";
            break;
    }
    return os;
}
