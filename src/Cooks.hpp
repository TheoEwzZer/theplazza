/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Cooks
*/

#pragma once

#include <iostream>
#include "Pizzas/IPizza.hpp"

using std::string;

namespace plazza {
    class ICooks {
        public:
            virtual ~ICooks() = default;
            virtual void cook() = 0;
    };

    class Cooks : public ICooks {
        public:
            Cooks(IPizza *const pizza, const double multiplier)
            : mPizza(pizza), mMultiplier(multiplier) {}
            ~Cooks() override = default;

            void cook() override;
        private:
            IPizza *mPizza;
            double mMultiplier;
    };
}
