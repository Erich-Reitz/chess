#include "Square.hpp"
#include "Position.hpp"

Square::Square(bool white, int _row, int _col, float xPos, float yPos, float size, std::optional<Piece*> _piece ) {
    this->position = Position(_row, _col);
    this->white = white;
    const auto scale_size_constant = .00125;
    this->shape.setScale(sf::Vector2f(size * scale_size_constant, size * scale_size_constant));
    this->shape.setPosition(sf::Vector2f(xPos, yPos));
    shape.setOrigin(shape.getLocalBounds().width/ 2, shape.getLocalBounds().height/ 2);
    std::string texture_path;

    if (white) {
        texture_path = "assets/textures/board_squares/light.png" ;

    } else {
        texture_path = "assets/textures/board_squares/dark.png" ;
    }

    if (texture.loadFromFile(texture_path)) {
        this->shape.setTexture(texture);

    } else {
        std::cout << "Error loading texture" << std::endl;
    }

    if (_piece.has_value()) {
        this->piece = _piece;
        this->piece.value()->setPosition(xPos + size/2, yPos+ size/2) ;
        this->piece.value()->setRadius(size / 2.0);

    } else {
        this->piece = {};
    }
}

Square::Square(const Square& rhs) :  white(rhs.white), piece(rhs.piece), shape(rhs.shape), position(rhs.position) {
    if (rhs.piece) {
        piece = std::make_optional<Piece*>(new Piece(**rhs.piece));

    } else {
        piece = std::nullopt;
    }
}

Square& Square::operator=(const Square& rhs) {
    if (this != &rhs) {
        white = rhs.white;
        shape = rhs.shape;
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
    target.draw(shape);

    if (piece.has_value()) {
        target.draw(*piece.value() );
    }
}

sf::FloatRect Square::getBoundaries() const {
    return shape.getGlobalBounds();
}

std::optional<Piece*> Square::getPiece() const {
    return this->piece;
}

void Square::setPiece(Piece *_piece) {
    this->piece = {_piece};
    sf::Vector2f currentSquarePosition = this->shape.getPosition();
    const auto square_position = this->shape.getPosition();
    this->piece.value()->setPosition(square_position.x+25, square_position.y+25);
}

void Square::removePiece() {
    this->piece = std::nullopt;
}

Position Square::getPosition() const {
    return position;
}

void Square::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
