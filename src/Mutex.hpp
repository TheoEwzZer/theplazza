/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Mutex
*/

#pragma once

#include <iostream>

namespace plazza {
    class IMutex {
        public:
            virtual ~IMutex() = default;
            virtual void lock() = 0;
            virtual void unlock() = 0;
            virtual bool trylock() = 0;
    };

    class Mutex : public IMutex {
        public:
            Mutex()
            {
                ::pthread_mutex_init(&mMutex, nullptr);
            }
            ~Mutex() override
            {
                ::pthread_mutex_destroy(&mMutex);
            }

            void lock() override
            {
                ::pthread_mutex_lock(&mMutex);
            }
            void unlock() override
            {
                ::pthread_mutex_unlock(&mMutex);
            }
            bool trylock() override
            {
                return ::pthread_mutex_trylock(&mMutex) == 0;
            }
        private:
            pthread_mutex_t mMutex;
    };
}
