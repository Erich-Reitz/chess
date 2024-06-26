#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "Board.hpp"
#include "DrawablePiece.hpp"


#include "add_sets.cpp"
#include "move_generation.hpp"
#include "chess_exceptions.hpp"
#include "bounded.hpp"
#include "oppositeColor.hpp"





Board::Board(std::unordered_map<std::string, sf::Texture *> l_textures) {
  this->mBoard = BoardStructure(l_textures);
}

Board::Board(const Board &rhs) {
  *this = rhs;
}

Board &Board::operator=(const Board &rhs) {
  this->mBoardState = rhs.mBoardState;
  this->mBoard = rhs.mBoard;
  return *this ;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  this->mBoard.draw(target, states);
}



std::optional<ValidPosition> Board::getRowAndColOfMouse(const sf::Vector2f mousePos) const {
  return mBoard.getRowAndColOfMouse(mousePos);
}


bool Board::unmovedRookAtPosition(const ValidPosition &pos) const {
  return mBoard.unmovedRookAtPosition(pos);
}


std::vector<ValidPosition> generateAllValidPositions() {
  std::vector<ValidPosition> allPositions;
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; ++j) {
      allPositions.push_back(ValidPosition(i, j));
    }
  }
  return allPositions;
}

bool moveCapturesPosition(const Move &move, const ValidPosition &pos) {
  if (!move.capturee.has_value()) {
    return false;
  }
  return move.capturee.value() == pos;
}

bool Board::king_is_attacked(PieceColor colorKingWeAreConcernedAbout) const {
  const auto positionOfColorKingWeAreConcernedAbout = mBoard.getKing(colorKingWeAreConcernedAbout);
  const auto opposite_color_of_king_we_are_concerned_about = opposite_color(colorKingWeAreConcernedAbout) ;
  for (const auto &position : generateAllValidPositions()) {
    auto allValidMoves = generateAllValidMovesForPieceAtPosition(position, false) ;
    for (auto valid_move : allValidMoves) {
      if (moveCapturesPosition(valid_move, positionOfColorKingWeAreConcernedAbout)) {
        return true;
      }
    }
  }
  return false;
}



void Board::processMove(const Move &move) {
  const auto currentColor = !this->mBoardState.colorToMove;
  if (move.isCapture()) {
    this->squareAt(move.capturee.value())->removePiece()  ;
  }
  switch (move.move_type) {
  case MoveType::PAWN_PROMOTION: {
    if (move.promoteTo == PieceType::QUEEN) {
      // auto squarePosition = this->squareAt(move)
      // auto *piece = new DrawablePiece(currentColor, PieceType::QUEEN, ) ;
      mBoard.movePiece(move.getOriginalSquare(), move.getDestination()) ;
    }
    break;
  }
  case MoveType::CASTLE: {
    const auto current_pos = move.castlee.value().first;
    const auto dest = move.castlee.value().second;
    mBoard.movePiece(current_pos, dest);
    break;
  }
  case MoveType::NORMAL:
    mBoard.movePiece(move.getOriginalSquare(), move.getDestination());
    break;
  default:
    throw RuntimeError() ;
  }
  this->mBoardState.processMove(move) ;
}



using move_function = std::function<std::vector<Move> (const Board *, const ValidPosition &, const DrawablePiece *)> ;

move_function move_gen_function(PieceType type) {
  static const std::unordered_map<PieceType, move_function> moveGeneratorMap = {
    {PieceType::ROOK, generateAllValidMovesForRook},
    {PieceType::BISHOP, generateAllValidMovesForBishop},
    {PieceType::QUEEN, generateAllValidMovesForQueen},
    {PieceType::KING, generateAllValidMovesForKing},
    {PieceType::KNIGHT, generateAllValidMovesForKnight},
    {PieceType::PAWN, generateAllValidMovesForPawn}
  };
  auto it = moveGeneratorMap.find(type);
  if (it != moveGeneratorMap.end())
    return it->second;
  throw PieceTypeSwitchFallthrough();
}


std::vector<Move> Board::generateAllValidMovesForPieceAtPosition(const ValidPosition &current,  bool careIfPlacesKingInCheck) const {
  const auto piece = pieceAtPosition(current) ;
  if (!piece.has_value()) {
    return {};
  }
  move_function generate_moves = move_gen_function(piece.value()->type);
  std::vector<Move> moves = generate_moves(this, current, piece.value());
  std::vector<Move> validMoves;
  std::copy_if(moves.begin(), moves.end(), std::inserter(validMoves, validMoves.end()),  [&](const Move & move) {
    return  legal_move(move, careIfPlacesKingInCheck) ;
  });
  return validMoves;
}

bool Board::legal_move(const Move &move, bool careIfPlacesKingInCheck) const {
  if (!careIfPlacesKingInCheck) {
    return true;
  }
  // after we process move, no pieces should have a valid move to attack king
  Board future_board = *this;
  // if white, we are processing white's move
  future_board.processMove(move) ;
  // now we want to see if black has a move to capture white's king
  // if it does, the previous move by white would place the king in check
  // and therefore be invalid
  return !future_board.king_is_attacked(this->mBoardState.colorToMove) ;
}


std::optional<DrawablePiece *> Board::pieceAtPosition(const ValidPosition &pos) const {
  return this->mBoard.pieceAtPosition(pos);
}

bool Board::hasPieceAtPosition(const ValidPosition &pos) const {
  return this->pieceAtPosition(pos).has_value();
}

bool Board::hasPieceAtPosition(const ValidPosition &pos, const PieceColor target_color) const {
  if (const auto piece = this->pieceAtPosition(pos).value_or(nullptr)) {
    return piece->color == target_color;
  }
  return false;
}

std::vector<Move> Board::getMoveList() const {
  return this->mBoardState.moveList;
}
PieceColor Board::getColorToMove() const {
  return this->mBoardState.colorToMove;
}


DrawableSquare *Board::squareAt(const ValidPosition &coord) const {
  return this->mBoard.squareAt(coord);
}

DrawableSquare *Board::squareAt(int i, int j) const {
  return this->mBoard.squareAt(ValidPosition(i, j) );
}




