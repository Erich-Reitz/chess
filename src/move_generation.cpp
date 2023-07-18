#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "move_generation.hpp"

#include "Board.hpp"
#include "DrawablePiece.hpp"
#include "add_sets.cpp"
#include "chess_exceptions.hpp"
#include "oppositeColor.hpp"




bool pieceCanBeCapturedEnPassant(DrawablePiece *piece_to_be_captured, ValidPosition piece_pos, const std::vector<Move> &moveList) {
  return (isPawnAndHasMovedOnceTwoSquaresForward(piece_to_be_captured, piece_pos) && moveList.back().getDestination() == piece_pos) ;
}


std::optional<ValidPosition>  findXSpacesForward(const ValidPosition &current, bool isPieceWhite, int spacesForward) {
  try {
    auto pos =  ValidPosition(current.r + (isPieceWhite ? - spacesForward : spacesForward), current.c) ;
    return pos;
  } catch(BoundConstraintViolation &e) {
  }
  return {};
}




std::vector<Move> generateAllValidMovesForPawn(const Board *board, const ValidPosition &currentPosition, const DrawablePiece *piece) {
  std::vector<Move> validMoves;
  const PieceColor pieceColor = piece->color;
  const PieceColor oppositeColorOfPiece = opposite_color(pieceColor) ;
  const bool pieceIsWhite = pieceColor == PieceColor::WHITE ;
  const std::optional<ValidPosition> potentialOneSpaceForward = findXSpacesForward(currentPosition, pieceIsWhite, 1) ;
  if (potentialOneSpaceForward.has_value() && !board->pieceAtPosition(potentialOneSpaceForward.value())) {
    const auto one_space_forward_move = std::make_pair(currentPosition, potentialOneSpaceForward.value()) ;
    validMoves.emplace_back(one_space_forward_move, pieceColor) ;
  }
  if (!piece->hasMoved()) {
    const std::optional<ValidPosition>  twoSpacesForward = findXSpacesForward(currentPosition, pieceIsWhite, 2) ;
    const auto two_space_forward_move = std::make_pair(currentPosition, twoSpacesForward.value()) ;
    if (twoSpacesForward.has_value() && !board->hasPieceAtPosition(potentialOneSpaceForward.value()) &&
        !board->hasPieceAtPosition(twoSpacesForward.value()) ) {
      validMoves.emplace_back(two_space_forward_move, pieceColor);
    }
  }
  try {
    auto squareToOneRight = ValidPosition(currentPosition.r, currentPosition.c +  (pieceIsWhite ? 1  : - 1)) ;
    const auto oneSpaceForwardOneSpaceRight = ValidPosition( currentPosition.r +  (pieceIsWhite ? - 1 : 1),
        currentPosition.c + (pieceIsWhite ? 1 : -1)) ;
    if (board->hasPieceAtPosition(oneSpaceForwardOneSpaceRight, oppositeColorOfPiece)) {
      const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceRight) ;
      validMoves.emplace_back(move, pieceColor, oneSpaceForwardOneSpaceRight );
    }
    const auto pieceOnSquareToTheRight = board->pieceAtPosition(squareToOneRight);
    if (pieceOnSquareToTheRight.has_value() &&
        pieceCanBeCapturedEnPassant(pieceOnSquareToTheRight.value(), squareToOneRight, board->getMoveList())) {
      const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceRight) ;
      validMoves.emplace_back(move, pieceColor, squareToOneRight) ;
    }
  } catch(BoundConstraintViolation &e) {
  }
  try {
    auto squareToOneLeft = ValidPosition(currentPosition.r, currentPosition.c + (pieceIsWhite ? -1 : 1)) ;
    const auto oneSpaceForwardOneSpaceLeft = ValidPosition(currentPosition.r +  (pieceIsWhite ? - 1 : 1),
        currentPosition.c + (pieceIsWhite ? -1 : 1)) ;
    if (board->hasPieceAtPosition(oneSpaceForwardOneSpaceLeft, oppositeColorOfPiece)) {
      const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceLeft) ;
      validMoves.emplace_back(move, pieceColor, oneSpaceForwardOneSpaceLeft) ;
    }
    const auto pieceOnSquareToTheLeft = board->pieceAtPosition(squareToOneLeft);
    if (pieceOnSquareToTheLeft.has_value() &&
        pieceCanBeCapturedEnPassant(pieceOnSquareToTheLeft.value(), squareToOneLeft, board->getMoveList())) {
      const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceLeft) ;
      validMoves.emplace_back(move, pieceColor, squareToOneLeft) ;
    }
  } catch(BoundConstraintViolation &e) {
  }
  for (auto &move : validMoves) {
    if (move.getDestination().r == 0 and move.colorMove == PieceColor::WHITE) {
      move.move_type = MoveType::PAWN_PROMOTION;
    } else if (move.getDestination().r == 7 and move.colorMove == PieceColor::BLACK)  {
      move.move_type = MoveType::PAWN_PROMOTION;
    }
  }
  return validMoves;
}

std::vector<Move> generateAllValidMovesForRook(const Board *board, const ValidPosition &current, const DrawablePiece *piece)  {
  const int row_difs[] = {-1, 1, 0, 0} ;
  const int col_difs[] = {0, 0, 1, -1} ;
  return generateMovesInStraightLine(board, current, piece->color, row_difs, col_difs) ;
}



std::vector<Move> generateAllValidMovesForQueen(const Board *board, const ValidPosition &current, const DrawablePiece *piece)  {
  std::vector<Move> allValidMoves = {};
  auto allValidMovesForBishop = generateAllDiagonalMoves(board, current, piece->color);
  auto allValidMovesForRook = generateAllValidMovesForRook(board, current, piece) ;
  add_sets(allValidMoves, allValidMovesForBishop, allValidMovesForRook) ;
  return allValidMoves;
}


std::vector<Move> generateAllValidMovesForBishop(const Board *board, const ValidPosition &current, const DrawablePiece *piece)  {
  return generateAllDiagonalMoves(board, current, piece->color) ;
}


std::vector<Move> generateMovesInStraightLine(const Board *board, const ValidPosition &currentPosition, PieceColor pieceColor,
    const int row_difs[], const int col_difs[])  {
  std::vector<Move> validMoves;
  PieceColor oppositePieceColor = opposite_color(pieceColor);
  for (int i = 0; i < 4; i++) {
    int row = currentPosition.r + row_difs[i] ;
    int col = currentPosition.c + col_difs[i] ;
    while (row >= 0 && col >= 0 && row < 8 && col < 8) {
      auto moveTo = ValidPosition(row, col) ;
      const std::pair<ValidPosition, ValidPosition> move = std::make_pair(currentPosition, moveTo);
      if (board->hasPieceAtPosition(moveTo, pieceColor)) {
        // blocked by same color
        break;
      }
      if (board->hasPieceAtPosition(moveTo, oppositePieceColor)) {
        validMoves.push_back(Move(move,pieceColor, moveTo)) ;
        break;
      }
      validMoves.push_back(Move(move,pieceColor)) ;
      row += row_difs[i] ;
      col += col_difs[i]  ;
    }
  }
  return validMoves;
}

std::vector<Move> generateAllDiagonalMoves(const Board *board, const ValidPosition &current, PieceColor color)  {
  const int row_difs[] = {-1, -1, 1, 1} ;
  const int col_difs[] = {-1, 1, 1, -1} ;
  return generateMovesInStraightLine(board, current, color, row_difs, col_difs) ;
}




std::vector<Move> generateAllValidMovesForKing(const Board *board, const ValidPosition &currentPosition, const DrawablePiece *piece)  {
  std::vector<Move> validMoves;
  PieceColor pieceColor = piece->color ;
  PieceColor oppositePieceColor = opposite_color(pieceColor);
  const int row_difs[] = {1, 1, 0, -1, -1, -1, 0, 1} ;
  const int col_difs[] = {0, 1, 1,  1,  0, -1, -1, -1} ;
  for (int i = 0; i < 8; i++) {
    auto row_dif = row_difs[i] ;
    auto col_dir = col_difs[i] ;
    try {
      auto moveTo = ValidPosition(currentPosition.r + row_dif, currentPosition.c + col_dir) ;
      const auto move = std::make_pair(currentPosition, moveTo);
      if (!board->hasPieceAtPosition(moveTo, pieceColor)) {
        if (board->hasPieceAtPosition(moveTo, oppositePieceColor)) {
          validMoves.push_back(Move(move,pieceColor, moveTo)) ;
        } else {
          validMoves.push_back(Move(move,pieceColor)) ;
        }
      }
    } catch (BoundConstraintViolation &e) {
    }
  }
  if (!piece->hasMoved()) {
    if (pieceColor == PieceColor::WHITE) {
      auto leftCorner = ValidPosition{7, 0};
      if (board->unmovedRookAtPosition(leftCorner)) {
        bool uninterruptedPathToLeftRook = true;
        for (int i = currentPosition.c - 1; i > 0; i--) {
          if (board->hasPieceAtPosition(ValidPosition{7, i})) {
            uninterruptedPathToLeftRook = false;
            break;
          }
        }
        if (uninterruptedPathToLeftRook) {
          auto castleMoveKingDest = ValidPosition{7, 2};
          auto castleMoveRookDest = ValidPosition{7, 3};
          const auto move = constructCastleMove(currentPosition, leftCorner, castleMoveKingDest, castleMoveRookDest, pieceColor) ;
          validMoves.push_back(move) ;
        }
      }
      auto rightCorner = ValidPosition{7, 7};
      if (board->unmovedRookAtPosition(rightCorner)) {
        bool uninterruptedPathToRightRook = true;
        for (int i = currentPosition.c + 1; i < 7; i++) {
          if (board->hasPieceAtPosition(ValidPosition{7, i})) {
            uninterruptedPathToRightRook = false;
            break;
          }
        }
        if (uninterruptedPathToRightRook) {
          auto castleMoveKingDest = ValidPosition{7, 6};
          auto castleMoveRookDest = ValidPosition{7, 5};
          const auto move = constructCastleMove(currentPosition, rightCorner, castleMoveKingDest, castleMoveRookDest, pieceColor) ;
          validMoves.push_back(move) ;
        }
      }
    } else if (pieceColor == PieceColor::BLACK) {
      auto leftCorner = ValidPosition{0, 0};
      if (board->unmovedRookAtPosition(leftCorner)) {
        bool uninterruptedPathToLeftRook = true;
        for (int i = currentPosition.c - 1; i > 0; i--) {
          if (board->hasPieceAtPosition(ValidPosition{0, i})) {
            uninterruptedPathToLeftRook = false;
            break;
          }
        }
        if (uninterruptedPathToLeftRook) {
          auto castleMoveKingDest = ValidPosition{0, 2};
          auto castleMoveRookDest = ValidPosition{0, 3};
          const auto move = constructCastleMove(currentPosition, leftCorner, castleMoveKingDest, castleMoveRookDest, pieceColor) ;
          validMoves.push_back(move) ;
        }
      }
      auto rightCorner = ValidPosition{0, 7};
      if (board->unmovedRookAtPosition(rightCorner)) {
        bool uninterruptedPathToRightRook = true;
        for (int i = currentPosition.c + 1; i < 7; i++) {
          if (board->hasPieceAtPosition(ValidPosition{0, i})) {
            uninterruptedPathToRightRook = false;
            break;
          }
        }
        if (uninterruptedPathToRightRook) {
          auto castleMoveKingDest = ValidPosition{0, 6};
          auto castleMoveRookDest = ValidPosition{0, 5};
          const auto move = constructCastleMove(currentPosition, rightCorner, castleMoveKingDest, castleMoveRookDest, pieceColor) ;
          validMoves.push_back(move) ;
        }
      }
    }
  }
  return validMoves ;
}

Move constructCastleMove(ValidPosition kingPosition, ValidPosition rookPosition, ValidPosition kingDest, ValidPosition rookDest,
                         PieceColor pieceColor) {
  const auto king_move = std::make_pair(kingPosition, kingDest);
  const auto rook_move = std::make_pair(rookPosition, rookDest);
  return Move(king_move, pieceColor, rook_move) ;
}

bool isPawnAndHasMovedOnceTwoSquaresForward(DrawablePiece *piece, ValidPosition piece_pos) {
  if (piece->type == PieceType::PAWN && piece->timesMoved == 1) {
    auto pieceIsWhite = piece->color == PieceColor::WHITE;
    return ((pieceIsWhite && piece_pos.r == 4) || (!pieceIsWhite && piece_pos.c==3)) ;
  }
  return false;
}

std::vector<Move> generateAllValidMovesForKnight(const Board *board, const ValidPosition &currentPosition, const DrawablePiece *piece)  {
  std::vector<Move> validMoves ;
  auto pieceColor = piece->color;
  auto oppositePieceColor = opposite_color(pieceColor);
  const int row_difs[] = {1, 1, -1, -1, 2, 2, -2, -2} ;
  const int col_difs[] = {2, -2, 2, -2, 1, -1, 1, -1} ;
  for (int i = 0; i < 8; i++) {
    auto row_dif = row_difs[i] ;
    auto col_dif = col_difs[i] ;
    try {
      auto moveTo = ValidPosition(currentPosition.r + row_dif, currentPosition.c + col_dif) ;
      const auto move = std::make_pair(currentPosition, moveTo);
      if (!board->hasPieceAtPosition(moveTo, pieceColor)) {
        if (board->hasPieceAtPosition(moveTo, oppositePieceColor)) {
          // capture
          validMoves.push_back(Move(move, pieceColor,  moveTo)) ;
        } else {
          // empty space
          validMoves.push_back(Move(move, pieceColor)) ;
        }
      }
    } catch(BoundConstraintViolation &e) {
    }
  }
  return validMoves;
}




