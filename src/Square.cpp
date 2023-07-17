#include "Square.hpp"

#include "chess_exceptions.hpp"

std::optional<Piece*> initial_piece(ValidPosition position, float squareXPos, float squareYPos) {
    auto row = position.r;
    auto col = position.c;
    bool isWhitePiece = row == 6 || row == 7;

    if (row == 0 || row == 7) {
        switch (col) {
        case 0:
            return new Piece(isWhitePiece, PieceType::ROOK, squareXPos, squareYPos) ;

        case 1:
            return new Piece(isWhitePiece, PieceType::KNIGHT, squareXPos, squareYPos) ;

        case 2:
            return new Piece(isWhitePiece, PieceType::BISHOP, squareXPos, squareYPos) ;

        case 3:
            return new Piece(isWhitePiece, PieceType::QUEEN, squareXPos, squareYPos) ;

        case 4:
            return new Piece(isWhitePiece, PieceType::KING, squareXPos, squareYPos) ;

        case 5:
            return new Piece(isWhitePiece, PieceType::BISHOP, squareXPos, squareYPos) ;

        case 6:
            return new Piece(isWhitePiece, PieceType::KNIGHT, squareXPos, squareYPos) ;

        case 7:
            return new Piece(isWhitePiece, PieceType::ROOK, squareXPos, squareYPos) ;

        default:
            throw RuntimeError();
        }
    }

    if (row == 1 || row == 6) {
        return new Piece(isWhitePiece, PieceType::PAWN,  squareXPos, squareYPos);
    }

    return {};
}

Square::Square(bool white, ValidPosition position, float xPos, float yPos,  float size ) : GameObject(xPos, yPos, size) {
    this->position = position;
    this->white = white;
    std::string texture_path;

    if (white) {
        texture_path = "assets/textures/board_squares/light.png" ;

    } else {
        texture_path = "assets/textures/board_squares/dark.png" ;
    }

    if (texture.loadFromFile(texture_path)) {
        this->sprite.setTexture(texture);

    } else {
        std::cout << "Error loading texture" << std::endl;
    }

    this->piece = initial_piece(position, xPos+25, yPos+25);

    if (this->piece.has_value()) {
        this->setPiece(this->piece.value()) ;
    }
}

void Square::setPieceSize() {
    this->piece.value()->setRadius(size / 2.0);
}

Square::Square(const Square& rhs) :  white(rhs.white), piece(rhs.piece), position(rhs.position) {
    if (rhs.piece) {
        piece = std::make_optional<Piece*>(new Piece(**rhs.piece));

    } else {
        piece = std::nullopt;
    }
}

Square& Square::operator=(const Square& rhs) {
    if (this != &rhs) {
        white = rhs.white;
        sprite = rhs.sprite;
        position = rhs.position;

        if (rhs.piece) {
            piece = std::make_optional<Piece*>(new Piece(**rhs.piece));

        } else {
            piece = std::nullopt;
        }
    }

    return *this;
}

void Square::draw(sf::RenderTarget& target) const {
    target.draw(sprite);

    if (piece.has_value()) {
        target.draw(*piece.value() );
    }
}

sf::FloatRect Square::getBoundaries() const {
    return sprite.getGlobalBounds();
}

std::optional<Piece*> Square::getPiece() const {
    return this->piece;
}

void Square::setPiece(Piece *_piece) {
    this->piece = {_piece};
    const auto square_position = this->sprite.getPosition();
    this->piece.value()->setPosition(square_position.x+25, square_position.y+25);
    this->setPieceSize();
}

void Square::removePiece() {
    this->piece = std::nullopt;
}

ValidPosition Square::getPosition() const {
    return position;
}

void Square::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
