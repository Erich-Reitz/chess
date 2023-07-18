#include "DrawableSquare.hpp"

#include "chess_exceptions.hpp"

std::optional<DrawablePiece *> initial_piece(ValidPosition position, float squareXPos, float squareYPos, std::optional<PieceType> pieceType,
    std::optional<sf::Texture *> piece_texture) {
  if (!pieceType) {
    return {};
  }
  bool isWhitePiece = position.r == 6 || position.r == 7;
  return new DrawablePiece(isWhitePiece, *pieceType, squareXPos, squareYPos, piece_texture.value());
}

DrawableSquare::~DrawableSquare() {
  if (const auto piece = this->m_piece.value_or(nullptr)) {
    delete piece;
  }
}


DrawableSquare::DrawableSquare(bool white, ValidPosition position, float xPos, float yPos, float size, std::optional<PieceType> pieceType,
                               sf::Texture *m_texture, std::optional<sf::Texture *> piece_texture) : GameObject(xPos, yPos, size, m_texture) {
  this->position = position;
  this->white = white;
  this->m_piece = initial_piece(position, xPos+25, yPos+25, pieceType, piece_texture);
  if (this->m_piece.has_value()) {
    this->setPiece(this->m_piece.value()) ;
  }
}

void DrawableSquare::setPieceSize() {
  this->m_piece.value()->setRadius(size / 2.0);
}

DrawableSquare::DrawableSquare(const DrawableSquare &rhs) : GameObject(rhs), white(rhs.white), m_piece(rhs.m_piece),
  position(rhs.position) {
  if (rhs.m_piece) {
    m_piece = std::make_optional<DrawablePiece *>(new DrawablePiece(**rhs.m_piece));
  } else {
    m_piece = std::nullopt;
  }
}

DrawableSquare &DrawableSquare::operator=(const DrawableSquare &rhs) {
  if (this != &rhs) {
    white = rhs.white;
    position = rhs.position;
    if (rhs.m_piece) {
      m_piece = std::make_optional<DrawablePiece *>(new DrawablePiece(**rhs.m_piece));
    } else {
      m_piece = std::nullopt;
    }
  }
  return *this;
}

void DrawableSquare::draw(sf::RenderTarget &target) const {
  target.draw(sprite);
  if (m_piece.has_value()) {
    target.draw(*m_piece.value() );
  }
}

sf::FloatRect DrawableSquare::getBoundaries() const {
  return sprite.getGlobalBounds();
}

std::optional<DrawablePiece *> DrawableSquare::getPiece() const {
  return this->m_piece;
}

void DrawableSquare::setPiece(DrawablePiece *_piece) {
  this->m_piece = {_piece};
  const auto square_position = this->sprite.getPosition();
  this->m_piece.value()->setPosition(square_position.x+25, square_position.y+25);
  this->setPieceSize();
}

void DrawableSquare::removePiece() {
  this->m_piece = std::nullopt;
}

ValidPosition DrawableSquare::getPosition() const {
  return position;
}

void DrawableSquare::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
