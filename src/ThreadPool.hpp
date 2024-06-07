/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** ThreadPool
*/

#pragma once

#include "Cooks.hpp"
#include "Logger.hpp"
#include "Thread.hpp"
#include <list>
#include <queue>
#include <thread>

using std::list;
using std::make_unique;
using std::queue;
using std::unique_ptr;

namespace plazza {
    class ThreadPool {
        public:
            ThreadPool(const size_t threads, Logger *logger);
            ~ThreadPool() = default;

            void exec();

            void add(ICooks *const order);
            [[nodiscard]] size_t getCooksAvailable() const;
        private:
            list<unique_ptr<Thread>> mCooks;
            queue<ICooks *> mTasks;
            Logger *mLogger;
    };
}
