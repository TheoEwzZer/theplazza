/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Process
*/

#pragma once

#include <iostream>
#include "Cooks.hpp"

namespace plazza {
    class IProcess {
        public:
            enum class STATUS {
                RUNNING,
                WAITING
            };
            virtual ~IProcess() = default;
    };

    class Process : public IProcess {
        public:
            explicit Process(ICooks &order);
            ~Process() override;
        private:
            pid_t mPid = 0;
            IProcess::STATUS mStatus = IProcess::STATUS::WAITING;
    };
}
