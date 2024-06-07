/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** APizza
*/

#pragma once

#include "IPizza.hpp"
#include <vector>
#include <ostream>
#include <unordered_map>
#include <memory>

using std::vector;
using std::ostream;
using std::string;
using std::unordered_map;
using std::unique_ptr;

namespace plazza {
    class APizza : public IPizza {
        public:
            ~APizza() override = default;
            PizzaType getType() const override;
            PizzaSize getSize() const override;
            int getCookTime() const override;
            vector<PizzaIngredient> getIngredients() const override;

            string getTypeString() const override;
            string getSizeString() const override;
            PizzaType getTypeByString(const string &type) const override;
            static PizzaSize getSizeByString(const string &size);

            string pack() const override;
            static IPizza *unpack(const string &data);
        protected:
            PizzaType mType;
            PizzaSize mSize;
            int mBakTime;
            vector<PizzaIngredient> mIngredients;
    };
};

ostream &operator<<(ostream &os, const plazza::PizzaType &type);
ostream &operator<<(ostream &os, const plazza::PizzaSize &size);
