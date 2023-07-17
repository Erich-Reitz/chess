#include <SFML/Graphics.hpp>

#include <set>

#include "Board.hpp"
#include "Piece.hpp"
#include "chess_exceptions.hpp"
#include "move_generation.hpp"




Piece::~Piece() = default;;

Piece::Piece(bool _white, PieceType _type, float squareXPos, float squareYPos, sf::Texture * texture  ) : GameObject(squareXPos, squareYPos, .0625, texture)  {
    if (_white) {
        this->color = PieceColor::WHITE;

    } else {
        this->color = PieceColor::BLACK;
    }

    this->type = _type;
    std::string piece_color_string;

    if (_white) {
        piece_color_string = "w";

    } else {
        piece_color_string = "b";
    }

    std::string piece_name_string ;

    switch (_type) {
    case PieceType::ROOK:
        m_moveFuncPtr = generateAllValidMovesForRook;
        piece_name_string = "rook";
        break;

    case PieceType::BISHOP:
        m_moveFuncPtr = generateAllValidMovesForBishop;
        piece_name_string = "bishop";
        break;

    case PieceType::QUEEN:
        m_moveFuncPtr = generateAllValidMovesForQueen;
        piece_name_string = "queen";
        break;

    case PieceType::KING:
        m_moveFuncPtr = generateAllValidMovesForKing;
        piece_name_string = "king";
        break;

    case PieceType::KNIGHT:
        m_moveFuncPtr = generateAllValidMovesForKnight;
        piece_name_string = "knight";
        break;

    case PieceType::PAWN:
        m_moveFuncPtr = generateAllValidMovesForPawn;
        piece_name_string = "pawn";
        break;

    default:
        throw PieceTypeSwitchFallthrough();
    }

    this->timesMoved = 0;
    const std::string texture_path = "assets/textures/pieces/no_shadow/2x/" + piece_color_string + "_" + piece_name_string  +"_2x_ns.png";
}

Piece::Piece(const Piece &rhs) : GameObject(rhs), timesMoved(rhs.timesMoved), color(rhs.color), type(rhs.type), m_moveFuncPtr(rhs.m_moveFuncPtr) {
}


Piece& Piece::operator=(const Piece& rhs){
    if (this != &rhs) {
        color = rhs.color;
        type = rhs.type;
        m_moveFuncPtr = rhs.m_moveFuncPtr;
        timesMoved = rhs.timesMoved;
    }

    return *this;
}


void Piece::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    sprite.setOrigin(sprite.getLocalBounds().width/ 2, sprite.getLocalBounds().height/ 2);
}

void Piece::setRadius(float radius) {
    if (this->type == PieceType::PAWN) {
        sprite.setScale(.065, .065);

    } else {
        sprite.setScale(.06, .06);
    }
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}


bool Piece::hasMoved() const {
    return this->timesMoved != 0;
}






