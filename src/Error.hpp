/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Error
*/


#pragma once

#include <stdexcept>
#include <string>

using std::exception;
using std::string;

namespace plazza {
    class InvalidArgument : public exception {
        public:
            explicit InvalidArgument(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class RuntimeError : public exception {
        public:
            explicit RuntimeError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };
}
