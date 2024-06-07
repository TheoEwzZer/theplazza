/*
** EPITECH PROJECT, 2024
** bstheplazza
** File description:
** SafeQueue
*/

#pragma once

#include <queue>
#include <mutex>
#include "ConditionVariable.hpp"

using std::queue;
using std::mutex;
using std::unique_lock;

namespace plazza {
    template <typename T>
    class ISafeQueue {
        public:
            virtual ~ISafeQueue() = default;
            virtual void push(T &&value) = 0;
            virtual bool tryPop(T &value) = 0;
            virtual T pop() = 0;
            virtual bool empty() const = 0;
            virtual T front() = 0;
    };

    template <typename T>
    class SafeQueue : public ISafeQueue<T> {
        public:
            void push(T &&value) override
            {
                unique_lock lock(mMutex);

                mQueue.push(move(value));
                lock.unlock();
                mCondVar.notifyOne();
            }
            bool tryPop(T &value) override
            {
                unique_lock lock(mMutex);

                if (mQueue.empty()) {
                    return false;
                }
                value = move(mQueue.front());
                mQueue.pop();
                return true;
            }
            T pop() override
            {
                unique_lock lock(mMutex);

                mCondVar.wait(lock, [this] { return !mQueue.empty(); });

                T value = move(mQueue.front());
                mQueue.pop();
                return value;
            }
            bool empty() const override
            {
                unique_lock lock(mMutex);
                return mQueue.empty();
            }
            T front() override
            {
                unique_lock lock(mMutex);
                return move(mQueue.front());
            }
        private:
            queue<T> mQueue;
            mutable mutex mMutex;
            ConditionVariable mCondVar;
    };
}
