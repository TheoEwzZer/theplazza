/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Regina
*/

#pragma once

#include "APizza.hpp"

using enum plazza::PizzaIngredient;

namespace plazza {
    class Regina : public APizza {
        public:
            explicit Regina(const PizzaSize &size)
            {
                mType = PizzaType::REGINA;
                mSize = size;
                mBakTime = 2;
                mIngredients = {DOUGH, TOMATO, GRUYERE, HAM, MUSHROOMS};
            }
            ~Regina() override = default;
    };
};
