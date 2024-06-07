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
    class Fantasia : public APizza {
        public:
            explicit Fantasia(const PizzaSize &size)
            {
                mType = PizzaType::FANTASIA;
                mSize = size;
                mBakTime = 4;
                mIngredients = {
                    DOUGH, TOMATO, EGGPLANT, GOAT_CHEESE, CHIEF_LOVE
                };
            }
            ~Fantasia() override = default;
    };
};
