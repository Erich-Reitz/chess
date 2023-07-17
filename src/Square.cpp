#include "Square.hpp"

#include "chess_exceptions.hpp"

std::optional<Piece *> initial_piece(ValidPosition position, float squareXPos, float squareYPos, std::optional<PieceType> pieceType,
                                     std::optional<sf::Texture *> piece_texture) {
  if (!pieceType) {
    return {};
  }
  bool isWhitePiece = position.r == 6 || position.r == 7;
  return new Piece(isWhitePiece, *pieceType, squareXPos, squareYPos, piece_texture.value());
}



Square::Square(bool white, ValidPosition position, float xPos, float yPos,  float size, std::optional<PieceType> pieceType,
               sf::Texture *m_texture, std::optional<sf::Texture *> piece_texture) : GameObject(xPos, yPos, size, m_texture) {
  this->position = position;
  this->white = white;
  this->piece = initial_piece(position, xPos+25, yPos+25, pieceType, piece_texture);
  if (this->piece.has_value()) {
    this->setPiece(this->piece.value()) ;
  }
}

void Square::setPieceSize() {
  this->piece.value()->setRadius(size / 2.0);
}

Square::Square(const Square &rhs) : GameObject(rhs),  white(rhs.white), piece(rhs.piece), position(rhs.position) {
  if (rhs.piece) {
    piece = std::make_optional<Piece *>(new Piece(**rhs.piece));
  } else {
    piece = std::nullopt;
  }
}

Square &Square::operator=(const Square &rhs) {
  if (this != &rhs) {
    white = rhs.white;
    position = rhs.position;
    if (rhs.piece) {
      piece = std::make_optional<Piece *>(new Piece(**rhs.piece));
    } else {
      piece = std::nullopt;
    }
  }
  return *this;
}

void Square::draw(sf::RenderTarget &target) const {
  target.draw(sprite);
  if (piece.has_value()) {
    target.draw(*piece.value() );
  }
}

sf::FloatRect Square::getBoundaries() const {
  return sprite.getGlobalBounds();
}

std::optional<Piece *> Square::getPiece() const {
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
