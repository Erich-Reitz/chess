#include <SFML/Graphics.hpp>

#include <set>

#include "Board.hpp"
#include "Piece.hpp"
#include "chess_exceptions.hpp"
#include "move_generation.hpp"




Piece::~Piece() = default;;

Piece::Piece(bool _white, PieceType _type)  {
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
        piece_name_string = "rook";
        break;

    case PieceType::BISHOP:
        piece_name_string = "bishop";
        break;

    case PieceType::QUEEN:
        piece_name_string = "queen";
        break;

    case PieceType::KING:
        piece_name_string = "king";
        break;

    case PieceType::KNIGHT:
        piece_name_string = "knight";
        break;

    case PieceType::PAWN:
        piece_name_string = "pawn";
        break;

    default:
        throw PieceTypeSwitchFallthrough();
    }

    this->timesMoved = 0;
    const std::string texture_path = "assets/textures/pieces/no_shadow/2x/" + piece_color_string + "_" + piece_name_string  +"_2x_ns.png";

    if (texture.loadFromFile(texture_path)) {
        this->piece.setTexture(texture);

    } else {
        std::cout << "Error loading texture" << std::endl;
    }
}

Piece::Piece(const Piece &rhs) : timesMoved(rhs.timesMoved), color(rhs.color), piece(rhs.piece), type(rhs.type) {
}


Piece& Piece::operator=(const Piece& rhs) {
    if (this != &rhs) {
        color = rhs.color;
        piece = rhs.piece;
        type = rhs.type;
        timesMoved = rhs.timesMoved;
    }

    return *this;
}


void Piece::setPosition(float x, float y) {
    piece.setPosition(x, y);
    piece.setOrigin(piece.getLocalBounds().width/ 2, piece.getLocalBounds().height/ 2);
}

void Piece::setRadius(float radius) {
    if (this->type == PieceType::PAWN) {
        piece.setScale(.065, .065);

    } else {
        piece.setScale(.06, .06);
    }
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(piece);
}


bool Piece::hasMoved() const {
    return this->timesMoved != 0;
}






