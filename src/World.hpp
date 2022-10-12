#pragma once
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Board.hpp"

class World  {

public:
    World();
    World(sf::Vector2f l_size);
    ~World();
    
    void update(sf::Time deltaTime);
    void Render(sf::RenderWindow& l_window);

    void HandleInput() ;
    void HandleInput(sf::Vector2i mousePos);

private:
    // updates
    Board gameBoard; 
    sf::Vector2f m_viewCenter;
    sf::Vector2f m_viewSize;


};