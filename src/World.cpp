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

void World::HandleInput(sf::Vector2f mousePos) {
    if (gameBoard.selectedPiece(mousePos).has_value()) {
        std::cout << "piece selected" << std::endl;
    } else {
        std::cout << "no piece selected" << std::endl;
    }
}


void World::Render(sf::RenderWindow& window) {
    window.draw(gameBoard);
}

void World::update(sf::Time deltaTime) {
}


