#include "DrawableSquare.hpp"

#include "chess_exceptions.hpp"

std::optional<DrawablePiece *> initial_piece(float squareXPos, float squareYPos, std::optional<PieceType> pieceType,
    std::optional<PieceColor> pieceColor,
    std::optional<sf::Texture *> piece_texture) {
  if (!pieceType) {
    return {};
  }
  return new DrawablePiece(pieceColor.value(), *pieceType, squareXPos, squareYPos, piece_texture.value());
}

DrawableSquare::~DrawableSquare() {
  if (const auto piece = this->m_piece.value_or(nullptr)) {
    delete piece;
  }
}


DrawableSquare::DrawableSquare(bool white,  float xPos, float yPos, float size, std::optional<PieceType> pieceType,
                               std::optional<PieceColor> pieceColor,
                               sf::Texture *m_texture, std::optional<sf::Texture *> piece_texture) : GameObject(xPos, yPos, size, m_texture) {
  this->white = white;
  this->m_piece = initial_piece( xPos+25, yPos+25, pieceType,pieceColor,  piece_texture);
  if (this->m_piece.has_value()) {
    this->setPiece(this->m_piece.value()) ;
  }
}

void DrawableSquare::setPieceSize() {
  this->m_piece.value()->setRadius(size / 2.0);
}

DrawableSquare::DrawableSquare(const DrawableSquare &rhs) : GameObject(rhs), white(rhs.white), m_piece(rhs.m_piece) {
  if (rhs.m_piece) {
    m_piece = std::make_optional<DrawablePiece *>(new DrawablePiece(**rhs.m_piece));
  } else {
    m_piece = std::nullopt;
  }
}

DrawableSquare &DrawableSquare::operator=(const DrawableSquare &rhs) {
  if (this != &rhs) {
    white = rhs.white;
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

std::optional<DrawablePiece *> DrawableSquare::piece() const {
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
void DrawableSquare::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
