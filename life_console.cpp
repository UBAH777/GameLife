#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Game.h"

int main() {
    Life life(10,10);
    new Game(life);
}
