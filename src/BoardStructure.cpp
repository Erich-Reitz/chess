#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "BoardStructure.hpp"
#include "Piece.hpp"


std::string getTextureNameFromPieceType(bool isWhite, PieceType _type) {
  std::string piece_color_string = isWhite ? "w" : "b";
  std::string piece_name_string;
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
    throw std::invalid_argument("Invalid Piece Type");
  }
  std::string texture_path = piece_color_string + "_" + piece_name_string + "_2x_ns.png";
  return texture_path;
}


std::optional<PieceType> initial_piece_type(ValidPosition position) {
  auto row = position.r;
  auto col = position.c;
  bool isWhitePiece = row == 6 || row == 7;
  if (row == 0 || row == 7) {
    switch (col) {
    case 0:
      return PieceType::ROOK;
    case 1:
      return  PieceType::KNIGHT;
    case 2:
      return  PieceType::BISHOP ;
    case 3:
      return  PieceType::QUEEN;
    case 4:
      return  PieceType::KING;
    case 5:
      return  PieceType::BISHOP;
    case 6:
      return  PieceType::KNIGHT ;
    case 7:
      return  PieceType::ROOK ;
    default:
      throw RuntimeError();
    }
  }
  if (row == 1 || row == 6) {
    return  PieceType::PAWN;
  }
  return {};
}


BoardStructure::BoardStructure(std::unordered_map<std::string, sf::Texture *> l_textures) {
  this->m_textures = l_textures;
  float initial_x_offset = 720.0;
  float initial_y_offset = 300.0;
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      bool isSquareWhite = (row + col) % 2 == 0;
      std::string texture_name = isSquareWhite ? "light.png" : "dark.png";
      ValidPosition pos = ValidPosition(row, col) ;
      auto pieceType = initial_piece_type(pos) ;
      std::optional<sf::Texture *> pieceTexture = {};
      bool isWhitePiece = row == 6 || row == 7;
      if (pieceType.has_value()) {
        std::string pieceTextureName = getTextureNameFromPieceType(isWhitePiece, pieceType.value()) ;
        pieceTexture = m_textures[pieceTextureName] ;
      }
      board[row][col] = new Square(isSquareWhite, pos, initial_x_offset + col * 50, initial_y_offset + row * 50, 0.0625, pieceType,
                                   m_textures[texture_name], pieceTexture);
    }
  }
}

BoardStructure::BoardStructure(const BoardStructure &rhs) {
  *this = rhs;
}


BoardStructure &BoardStructure::operator=(const BoardStructure &rhs) {
  board.resize(8);
  for (int i = 0; i < 8; i++) {
    board[i].resize(8);
    for (int j = 0; j < 8; j++) {
      board[i][j] = new Square(*rhs.board[i][j]);
    }
  }
  return *this ;
}

void BoardStructure::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto &row : board) {
    for (const auto &square : row) {
      square->draw(target);
    }
  }
}

std::optional<ValidPosition> BoardStructure::getRowAndColOfMouse(const sf::Vector2f mousePos) const {
  for (const auto &row : this->board) {
    for (const auto &square : row) {
      if (square->getBoundaries().contains(mousePos)) {
        return square->getPosition();
      }
    }
  }
  return {};
}

Square *BoardStructure::squareAt(const ValidPosition &coord) const {
  return this->board.at(coord.r).at(coord.c);
}


Square *BoardStructure::squareAt(int row, int col) const {
  return this->board.at(row).at(col);
}