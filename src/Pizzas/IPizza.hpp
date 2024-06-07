/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** IPizza
*/

#pragma once

#include <vector>
#include <ostream>
#include <memory>
#include <format>

using std::ostream;
using std::vector;
using std::string;
using std::unique_ptr;
using std::format;

namespace plazza {
    enum class PizzaType
    {
        REGINA = 1,
        MARGARITA = 2,
        AMERICANA = 4,
        FANTASIA = 8
    };
    enum class PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    enum class PizzaIngredient
    {
        CHIEF_LOVE,
        DOUGH,
        EGGPLANT,
        GOAT_CHEESE,
        GRUYERE,
        HAM,
        MUSHROOMS,
        STEAK,
        TOMATO,
    };
    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual PizzaType getType() const = 0;
            virtual PizzaSize getSize() const = 0;
            virtual int getCookTime() const = 0;
            virtual vector<PizzaIngredient> getIngredients() const = 0;

            virtual string getTypeString() const = 0;
            virtual string getSizeString() const = 0;
            virtual PizzaType getTypeByString(const string &type) const = 0;
            virtual string pack() const = 0;
    };
};
