#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include <iostream>

const std::string CONFIG = "../config/config.txt";

int main()
{
    auto game = Game(CONFIG);
    game.run();
    return 0;
}