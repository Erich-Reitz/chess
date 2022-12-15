#include "Square.hpp"
#include "Position.hpp"

Square::Square(bool white, int _row, int _col, float xPos, float yPos, float size, std::optional<Piece*> _piece ) {
    this->position = Position(_row, _col);
    this->white = white;
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setPosition(sf::Vector2f(xPos, yPos));
    if (white) {
        this->shape.setFillColor(sf::Color::Yellow);
    } else {
        this->shape.setFillColor(sf::Color::Magenta);
    }
    if (_piece.has_value()) {
        this->piece = _piece;
        this->piece.value()->setPosition(xPos, yPos) ;
        this->piece.value()->setRadius(size / 2.0);
    }
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
    this->piece.value()->setPosition(currentSquarePosition.x, currentSquarePosition.y);
}

void Square::removePiece() {
    this->piece = std::nullopt;
}

Position Square::getPosition() const {
    return position;
}

// unused
void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {}