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
    class Margarita : public APizza {
        public:
            explicit Margarita(const PizzaSize &size)
            {
                mType = PizzaType::MARGARITA;
                mSize = size;
                mBakTime = 1;
                mIngredients = {DOUGH, TOMATO, GRUYERE};
            }
            ~Margarita() override = default;
    };
};
