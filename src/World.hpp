#pragma once
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Board.hpp"
#include "SelectedPieceInfo.hpp"

class World  {

  public:
    World();
    ~World();

    void update(sf::Time deltaTime);
    void Render(sf::RenderWindow& l_window);

    void HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp);

  private:
    void handleMouseDownWithSelectedPiece(const ValidPosition& pressedSquare);
    void handleMouseDownWithNoSelectedPiece(const ValidPosition& pressedSquare);
    void handleMouseDown(sf::Vector2f mousePos);
    void handleMouseDownOnSquare(const ValidPosition& pressedCoordinates);
    // updates
    Board gameBoard;
    sf::Vector2f m_viewCenter;
    sf::Vector2f m_viewSize;
    SelectedPieceInformation selectedPieceInformation;


    void moveSelectedPiece(const ValidPosition &destination);

    void handleUserReselectingPiece(const ValidPosition &pressuredSquare);

    void displayValidMoves();

    void displaySelectedPiece();
};