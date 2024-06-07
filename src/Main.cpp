/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Main
*/

#include <iostream>
#include "Reception.hpp"

using std::cerr;
using std::cout;
using std::strtod;
using std::strtol;

int main(int argc, char **argv)
{
    char *end = nullptr;
    double multiplier = 0.0;
    long cooks = 0;
    long time = 0;

    if (argc != 4) {
        cerr << "Error: Invalid number of arguments\n";
        return 84;
    }
    multiplier = ::strtod(argv[1], &end);
    if ((end == argv[1]) || (*end != '\0') || (multiplier < 0)) {
        cerr << "Error: The first argument must be a positive number\n";
        return 84;
    }
    cooks = ::strtol(argv[2], &end, 10);
    if ((end == argv[2]) || (*end != '\0') || (cooks <= 0)) {
        cerr << "Error: The second argument must be a positive number\n";
        return 84;
    }
    time = ::strtol(argv[3], &end, 10);
    if ((end == argv[3]) || (*end != '\0') || (time <= 0)) {
        cerr << "Error: The third argument must be a positive number\n";
        return 84;
    }
    plazza::Reception reception(multiplier, cooks, time);
    reception.startPlazza();
    return 0;
}
