/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Pipe
*/

#pragma once

#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using std::string;
using std::ifstream;
using std::ofstream;

namespace plazza {
    class IPipe {
        public:
            explicit IPipe(const string &path) : mPath(path) {};
            virtual ~IPipe() = default;
        protected:
            string mPath;
    };

    class PipeIn : public IPipe {
        public:
            explicit PipeIn(const string &path);
            ~PipeIn() override;

            PipeIn &operator>>(string &data);
            void read(string &data);
        private:
            ifstream mStream;
    };

    class PipeOut : public IPipe {
        public:
            explicit PipeOut(const string &path);
            ~PipeOut() override;

            PipeOut &operator<<(const string &data);
            void write(const string &data);
        private:
            ofstream mStream;
    };
};
