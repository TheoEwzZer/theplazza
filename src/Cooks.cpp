/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Cooks
*/

#include "Cooks.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;

void plazza::Cooks::cook()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(
        static_cast<long>(mMultiplier * mPizza->getCookTime() * 1000)
    ));
    cout << "COOK: a " <<  mPizza->pack() << " is ready! Enjoy your meal!\n";
}
