/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** ConditionVariable
*/

#pragma once

#include <condition_variable>
#include <mutex>

using std::condition_variable;
using std::mutex;
using std::unique_lock;

namespace plazza {
    class IConditionVariable {
        public:
            virtual ~IConditionVariable() = default;
            virtual void notifyOne() = 0;
            virtual void notifyAll() = 0;
    };

    class ConditionVariable : public IConditionVariable {
        public:
            ConditionVariable() = default;
            ~ConditionVariable() override = default;

            template<class Predicate>
            void wait(unique_lock<mutex> &lock, Predicate pred)
            {
                cv.wait(lock, pred);
            }

            void notifyOne() noexcept override
            {
                cv.notify_one();
            }

            void notifyAll() noexcept override
            {
                cv.notify_all();
            }
        private:
            condition_variable cv;
    };
}
