#include "World.hpp"
#include "Board.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

World::World() {
}

World::World(sf::Vector2f l_size) {
}

World::~World() {}

void World::HandleInput(sf::Vector2i mousePos) {
}


void World::Render(sf::RenderWindow& window) {
    std::cout << "World::Render" << std::endl;
    window.draw(gameBoard);
}

void World::update(sf::Time deltaTime) {
}


