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
    class Americana : public APizza {
        public:
            explicit Americana(const PizzaSize &size)
            {
                mType = PizzaType::AMERICANA;
                mSize = size;
                mBakTime = 2;
                mIngredients = {DOUGH, TOMATO, GRUYERE, STEAK};
            }
            ~Americana() override = default;
    };
};
