/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Process
*/

#include "Process.hpp"
#include <sys/types.h>
#include <sys/wait.h>

plazza::Process::Process(ICooks &order)
{
    mPid = ::fork();
    if (mPid == 0) {
        order.cook();
        ::exit(0);
    } else {
        mStatus = IProcess::STATUS::RUNNING;
    }
}

plazza::Process::~Process()
{
    if (mStatus == IProcess::STATUS::RUNNING) {
        ::waitpid(mPid, nullptr, 0);
    }
}
