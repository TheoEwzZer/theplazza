/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"
#include "Logger.hpp"
#include <format>

using std::format;

plazza::ThreadPool::ThreadPool(const size_t threads, Logger *logger)
    : mLogger(logger)
{
    for (size_t i = 0; i < threads; i++) {
        mCooks.push_back(make_unique<Thread>());
        mLogger->log(format("COOK: Cook {} is ready", i));
    }
}

void plazza::ThreadPool::add(ICooks *const order)
{
    mTasks.push(order);
}

void plazza::ThreadPool::exec()
{
    for (auto const &thread : mCooks) {
        if (mTasks.empty()) {
            break;
        }
        if (thread->status() == Thread::Status::WAITING) {
            thread->run(mTasks.front());
            mTasks.pop();
        }
    }
}

size_t plazza::ThreadPool::getCooksAvailable() const
{
    size_t availableCooks = 0;

    for (auto const &thread : mCooks) {
        if (thread->status() == Thread::Status::WAITING) {
            availableCooks++;
        }
    }
    return availableCooks;
}
