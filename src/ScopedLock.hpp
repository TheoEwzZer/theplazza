/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** ScopedLock
*/

#pragma once

#include <iostream>
#include "Mutex.hpp"

namespace plazza {
    class ScopedLock {
        public:
            explicit ScopedLock(Mutex &mutex) : mMutex(mutex)
            {
                mMutex.lock();
            }
            ~ScopedLock()
            {
                mMutex.unlock();
            }
        private:
            Mutex &mMutex;
    };
}
