#pragma once
#include <optional>

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
    void HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp);

  private:
    bool havePreviouslySelectedCoordinates() const;
    void handleMouseDownWithSelectedPiece(Position pressedSquare);
    void handleMouseDownWithNoSelectedPiece(Position pressedSquare);
    void handleMouseDown(sf::Vector2f mousePos);
    void handleMouseDownOnSquare(Position pressedCoordinates);
    // updates
    Board gameBoard;
    sf::Vector2f m_viewCenter;
    sf::Vector2f m_viewSize;
    std::optional<Position> previouslySelectedCoordinatesOfPiece;


};