#pragma once
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Board.hpp"
#include "SelectedPieceInfo.hpp"

enum WORLD_STATE {
    BOARD,
    PAWN_PROMOTION_DIALOG
} ;

class World  {

  public:
    World();
    ~World();

    void update(sf::Time deltaTime);
    void Render(sf::RenderWindow& l_window);

    void HandleInput(sf::Vector2f mousePos, bool mouseDown, bool mouseUp);

  private:
    void handleMouseDownOnBoardWithSelectedPiece(const ValidPosition& pressedSquare);
    void handleMouseDownOnBoardWithNoSelectedPiece(const ValidPosition& pressedSquare);
    void handleMouseDown(sf::Vector2f mousePos);
    void handleMouseDownOnBoard(sf::Vector2f mousePos) ;

    void handleMouseDownOnSquare(const ValidPosition& pressedCoordinates);
    void handleMouseDownOnPawnPromotionDialog(sf::Vector2f mousePos) ;
    void displayPawnPromotionDialog();


    // updates
    Board gameBoard;
    sf::Vector2f m_viewCenter;
    sf::Vector2f m_viewSize;
    SelectedPieceInformation selectedPieceInformation;
    sf::RectangleShape pawnPromotionDialog ;
    WORLD_STATE worldState = BOARD;

    void moveSelectedPiece(const ValidPosition &destination);

    void handleUserReselectingPiece(const ValidPosition &pressedSquare);

    void displayValidMoves();

    void displaySelectedPiece();

    void clearSelectedPieceInformation();
};