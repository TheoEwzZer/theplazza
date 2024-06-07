/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Logger
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::ofstream;
using std::string;

namespace plazza {
    class Logger {
        public:
            Logger();
            ~Logger();
            void log(const string &message);
        private:
            ofstream mLogFile;
    };
}
