#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include "Square.hpp"

class Board : public sf::Drawable {
  public:
    Board();
    void draw(sf::RenderWindow &window) const  {};
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::optional<Piece*> selectedPiece(sf::Vector2f mousePos) const;
    std::optional<Square*> selectedSquare(sf::Vector2f mousePos) const;

    std::optional<Piece*> pieceAtPosition(Position pos) const;
    bool hasPieceAtPosition(Position pos) const ;

    bool canMove(Position current, Position destination) const;
    void move(Position current, Position destination);

    std::optional<Position> getRowAndColOfMouse(sf::Vector2f mousePos) const;
  protected:
    std::vector<std::vector<Square*>> board = std::vector<std::vector<Square*>> (8, std::vector<Square*>(8));
    void removePieceFromSquare(Position coordinates);
    std::vector<Position> generateAllValidMovesForPiece(Position current, Piece *piece) const;
};
