#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include <iostream>


int main()
{
    std::string config = "config";
    auto game = Game(config);
    game.run();
    return 0;
}