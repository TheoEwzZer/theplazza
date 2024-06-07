/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Kitchen
*/

#pragma once

#include "ConditionVariable.hpp"
#include "Cooks.hpp"
#include "Logger.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "Pizzas/APizza.hpp"
#include "Pizzas/IPizza.hpp"
#include "Process.hpp"
#include "SafeQueue.hpp"
#include "ThreadPool.hpp"
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

using enum plazza::PizzaIngredient;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::cout;
using std::make_unique;
using std::map;
using std::mutex;
using std::size_t;
using std::string;
using std::unique_lock;
using std::unique_ptr;
using std::unordered_map;

namespace plazza {
    class Kitchen : public ICooks {
    public:
        Kitchen(
            const string &pathIn, const string &pathOut,
            const double multiplier, const size_t cooks,
            const size_t time, Logger *logger
        );
        ~Kitchen() override = default;

        [[nodiscard]] bool isKitchenAlive() const;
        string ingredientToString(const PizzaIngredient size) const;
        void addPizza(unique_ptr<IPizza> pizza);
        void checkClose();
        void refreshFrigo();
        void handleOrder(string &order);
        void getAvailableCooks(const string &arg);
        void status(const string &arg);
        void canCook(const string &arg);
        [[noreturn]] void close(const string &arg);
        void cook(const string &arg);
        void cook() override;
    private:
        bool mIsAlive = true;
        ConditionVariable mCondition;
        double mMultiplier = 0.0;
        SafeQueue<unique_ptr<IPizza>> mPizzas;
        size_t mCooksMaxNumber = 0;
        size_t mTime = 0;
        unique_ptr<ThreadPool> mCook;
        map<PizzaIngredient, size_t> mFrigo = {
            {CHIEF_LOVE, 5},
            {DOUGH, 5},
            {EGGPLANT, 5},
            {GOAT_CHEESE, 5},
            {GRUYERE, 5},
            {HAM, 5},
            {MUSHROOMS, 5},
            {STEAK, 5},
            {TOMATO, 5}
        };
        string mPathIn;
        string mPathOut;
        PipeIn *mPipeIn = nullptr;
        PipeOut *mPipeOut = nullptr;
        Logger *mLogger = nullptr;

        using CommandFunc = void (Kitchen::*)(const string &arg);
        std::unordered_map<std::string, CommandFunc> mCommandMap;
    };
}
