/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Pipe
*/

#include "Pipe.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Error.hpp"

plazza::PipeIn::PipeIn(const string &path) : IPipe(path)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    if (
        (::access(mPath.c_str(), R_OK) == -1) &&
        (::mkfifo(mPath.c_str(), 0644) == -1))
    {
        throw RuntimeError("Cannot create Input pipe");
    }
    mStream.open(mPath);
    if (mStream.fail()) {
        throw RuntimeError("Cannot open Input pipe");
    }
}

plazza::PipeIn::~PipeIn()
{
    mStream.close();
    ::unlink(mPath.c_str());
}

plazza::PipeIn &plazza::PipeIn::operator>>(string &data)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    mStream >> data;
    return *this;
}

void plazza::PipeIn::read(string &data)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    mStream >> data;
}

plazza::PipeOut::PipeOut(const string &path) : IPipe(path)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    if (
        (::access(mPath.c_str(), W_OK) == -1) &&
        (::mkfifo(mPath.c_str(), 0644) == -1))
    {
        throw RuntimeError("Cannot create Output pipe");
    }
    mStream.open(mPath);
    if (mStream.fail()) {
        throw RuntimeError("Cannot open Output pipe");
    }
}

plazza::PipeOut::~PipeOut()
{
    mStream.close();
    ::unlink(mPath.c_str());
}

plazza::PipeOut &plazza::PipeOut::operator<<(const string &data)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    mStream << data << "\n" << std::flush;
    return *this;
}

void plazza::PipeOut::write(const string &data)
{
    Mutex mutex;
    const ScopedLock lock(mutex);

    mStream << data << "\n" << std::flush;
}
