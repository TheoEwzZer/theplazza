/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Logger
*/

#include "Logger.hpp"

using std::flush;

plazza::Logger::Logger()
{
    mLogFile.open("orders.log", std::ios::out);
    if (!mLogFile) {
        cerr << "Failed to open log file\n";
    }
}

plazza::Logger::~Logger()
{
    if (mLogFile.is_open()) {
        mLogFile.close();
    }
}

void plazza::Logger::log(const string &message)
{
    cout << message << "\n" << flush;
    mLogFile << message << "\n" << flush;
}
