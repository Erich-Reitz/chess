#include <SFML/Graphics.hpp>

#include <set>

#include "Board.hpp"
#include "Piece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "Position.hpp"




Piece::~Piece() = default;;

Piece::Piece(bool _white, PieceType _type)  {
    if (_white) {
        this->color = PieceColor::WHITE;

    } else {
        this->color = PieceColor::BLACK;
    }

    this->type = _type;

    if (_white) {
        piece.setFillColor(sf::Color::White);

        if (_type == PieceType::KING) {
            piece.setFillColor(sf::Color::Blue) ;
        }

    } else {
        piece.setFillColor(sf::Color::Black);

        if (_type == PieceType::KING) {
            piece.setFillColor(sf::Color::Blue) ;
        }
    }

    switch (_type) {
    case PieceType::ROOK:
        generateMovesFn = &Board::generateAllValidMovesForRook;
        break;

    case PieceType::BISHOP:
        generateMovesFn = &Board::generateAllValidMovesForBishop;
        break;

    case PieceType::QUEEN:
        generateMovesFn = &Board::generateAllValidMovesForQueen;
        break;

    case PieceType::KING:
        generateMovesFn = &Board::generateAllValidMovesForKing;
        break;

    case PieceType::KNIGHT:
        generateMovesFn = &Board::generateAllValidMovesForKnight;
        break;

    case PieceType::PAWN:
        generateMovesFn = &Board::generateAllValidMovesForPawn;
        break;
    }

    this->timesMoved = 0;
}

Piece::Piece(const Piece &rhs) : color(rhs.color), piece(rhs.piece), type(rhs.type), generateMovesFn(rhs.generateMovesFn), timesMoved(rhs.timesMoved) {
}


Piece& Piece::operator=(const Piece& rhs) {
    if (this != &rhs) {
        color = rhs.color;
        piece = rhs.piece;
        type = rhs.type;
        generateMovesFn = rhs.generateMovesFn;
        timesMoved = rhs.timesMoved;
    }

    return *this;
}


void Piece::setPosition(float x, float y) {
    piece.setPosition(x, y);
}

void Piece::setRadius(float radius) {
    piece.setRadius(radius);
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(piece);
}

bool Piece::isWhite() const {
    return this->color == PieceColor::WHITE;
}

bool Piece::hasMoved() const {
    return this->timesMoved != 0;
}

void Piece::setColor(sf::Color color) {
    this->piece.setFillColor(color);
}

void Piece::setMoved() {
    this->timesMoved += 1;
}

PieceType Piece::getType() const {
    return this->type;
}

void Piece::setOriginalColor() {
    if (isWhite()) {
        setColor(sf::Color::White);

    } else {
        setColor(sf::Color::Black);
    }
}

size_t Piece::getTimesMoved() const {
    return this->timesMoved;
}



