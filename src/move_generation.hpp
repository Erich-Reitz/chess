#pragma once

#include <vector>
#include "PieceType.hpp"

#include "Move.hpp"
#include "Board.hpp"
std::vector<Move> generateMovesInStraightLine(const Board *board, const Position& currentPosition, PieceColor pieceColor, const int row_difs[], const int col_difs[]) ;

PieceColor opposite_color(PieceColor color);

bool positionInBoard(const Position &pos) ;

std::vector<Move> generateAllDiagonalMoves(const Board *board, const Position& current, PieceColor color);

bool isPawnAndHasMovedOnceTwoSquaresForward(Piece *piece, Position piece_pos) ;

std::vector<Move> generateAllValidMovesForQueen(const Board *board, const Position& current, const Piece *piece) ;

std::vector<Move> generateAllValidMovesForPawn(const Board *board, const Position& currentPosition, const Piece *piece) ;

std::vector<Move> generateAllValidMovesForKnight(const Board *board, const Position& currentPosition, const Piece *piece) ;

std::vector<Move> generateAllValidMovesForRook(const Board *board, const Position& currentPosition, const Piece *piece);

std::vector<Move> generateAllValidMovesForBishop(const Board *board, const Position& currentPosition, const Piece *piece) ;

std::vector<Move> generateAllValidMovesForKing(const Board *board, const Position& currentPosition, const Piece *piece) ;