/*
** EPITECH PROJECT, 2024
** bstheplazza
** File description:
** Thread
*/

#pragma once

#include "Cooks.hpp"
#include "Error.hpp"
#include <functional>
#include <memory>
#include <pthread.h>
#include <stdexcept>

using std::make_unique;
using std::unique_ptr;

namespace plazza {
    class Thread {
    public:
        enum class Status {
            WAITING,
            RUNNING,
            DEAD
        };

        Thread() = default;
        ~Thread();
        template <typename StartRoutine>
        void start(StartRoutine startRoutine, void *const arg)
        {
            using enum plazza::Thread::Status;
            if (mStatus == RUNNING) {
                throw RuntimeError("Thread is already running");
            }
            if (mStatus == DEAD) {
                throw RuntimeError("Thread is dead");
            }
            mStatus = RUNNING;
            if (::pthread_create(&mThread, nullptr, startRoutine, arg) != 0) {
                throw RuntimeError("Failed to create thread");
            }
        }
        void run(ICooks *const order);
        [[nodiscard]] Status status() const;
        static void *startThreadRoutine(void *arg);
        pthread_t mThread = 0;
        Status mStatus = Status::WAITING;
        ICooks *mOrder;
    };
}
