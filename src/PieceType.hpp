#pragma once
enum PromotablePieceType { PROMOTE_TO_ROOK = 0, PROMOTE_TO_KNIGHT = 1, PROMOTE_TO_BISHOP = 2, PROMOTE_TO_QUEEN = 3, } ;

enum PieceType { PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5} ;

enum PieceColor {WHITE = 0, BLACK = 1};

enum MoveType {NORMAL,  PAWN_PROMOTION, CASTLE } ;