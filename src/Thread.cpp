/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Thread
*/

#include "Thread.hpp"

using enum plazza::Thread::Status;

plazza::Thread::~Thread()
{
    if (mStatus == RUNNING) {
        mStatus = DEAD;
        ::pthread_exit(nullptr);
    }
}

void plazza::Thread::run(ICooks *const order)
{
    mOrder = order;
    if (mStatus == RUNNING) {
        throw RuntimeError("Thread is already running");
    }
    if (mStatus == DEAD) {
        throw RuntimeError("Thread is dead");
    }
    mStatus = RUNNING;
    if (::pthread_create(&mThread, nullptr, startThreadRoutine, this) != 0) {
        throw RuntimeError("Failed to create thread");
    }
}

plazza::Thread::Status plazza::Thread::status() const
{
    return mStatus;
}

void *plazza::Thread::startThreadRoutine(void *const arg)
{
    auto *const thread = static_cast<Thread*>(arg);

    thread->mOrder->cook();
    thread->mStatus = WAITING;
    return nullptr;
}
