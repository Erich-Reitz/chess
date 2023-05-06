#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "move_generation.hpp"

#include "Board.hpp"
#include "Piece.hpp"
#include "Position.hpp"


#include "add_sets.cpp"

#include "chess_exceptions.hpp"

PieceColor opposite_color(PieceColor color) {
    return color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE ;
}


bool positionInBoard(const Position &pos)  {
    return (pos.row >= 0 && pos.row < 8) && pos.col < 8 && pos.col >= 0;
}

bool pieceCanBeCapturedEnPassant(Piece *piece_to_be_captured, Position piece_pos, const std::vector<Move> &moveList) {
    return (isPawnAndHasMovedOnceTwoSquaresForward(piece_to_be_captured, piece_pos) && moveList.back().move.second == piece_pos) ;
}

Position findOneSpaceForward(const Position& current, bool isPieceWhite) {
    return Position(current.row +  (isPieceWhite ? - 1 : 1), current.col) ;
}

Position findOneSpaceRight(const Position& current, bool isPieceWhite) {
    return Position(current.row, current.col +  (isPieceWhite ? 1  : - 1)) ;
}

Position findOneSpaceLeft(const Position& current, bool isPieceWhite) {
    return  Position(current.row, current.col + (isPieceWhite ? -1 : 1)) ;
}

bool Board::legal_move(const Move &move, bool careIfPlacesKingInCheck) const {
    if (careIfPlacesKingInCheck) {
        const auto pos_in_board = positionInBoard(move.move.second);

        if (!pos_in_board) {
            return false;
        }

        const auto move_finishes_with_king_in_check = moves_finishes_with_king_in_check(move);

        if (move_finishes_with_king_in_check) {
            return false;
        }
    }

    return positionInBoard(move.move.second) ;
}



std::vector<Move> generateAllValidMovesForPawn(const Board *board, const Position& currentPosition, const Piece *piece) {
    std::vector<Move> validMoves;
    const PieceColor pieceColor = piece->getColor();
    const PieceColor oppositeColorOfPiece = opposite_color(pieceColor) ;
    const bool pieceIsWhite = pieceColor == PieceColor::WHITE ;
    const Position oneSpaceForward = findOneSpaceForward(currentPosition, pieceIsWhite) ;
    const Position oneSpaceRight = findOneSpaceRight(currentPosition, pieceIsWhite);
    const Position oneSpaceLeft = findOneSpaceLeft(currentPosition, pieceIsWhite) ;
    const Position oneSpaceForwardOneSpaceRight = Position(currentPosition.row +  (pieceIsWhite ? - 1 : 1), currentPosition.col + (pieceIsWhite ? 1 : -1)) ;
    const Position oneSpaceForwardOneSpaceLeft = Position(currentPosition.row +  (pieceIsWhite ? - 1 : 1), currentPosition.col + (pieceIsWhite ? -1 : 1)) ;

    if (!piece->hasMoved()) {
        const Position twoSpacesForward = Position(currentPosition.row + (pieceIsWhite ? - 2 : 2), currentPosition.col) ;
        const auto two_space_forward_move = std::make_pair(currentPosition, twoSpacesForward) ;

        if (!board->hasPieceAtPosition(oneSpaceForward) && !board->hasPieceAtPosition(twoSpacesForward) ) {
            validMoves.push_back(Move(two_space_forward_move, pieceColor));
        }
    }

    if (!board->hasPieceAtPosition(oneSpaceForward)) {
        const auto move = std::make_pair(currentPosition, oneSpaceForward) ;
        validMoves.push_back(Move(move, pieceColor) );
    }

    if (board->hasPieceAtPosition(oneSpaceForwardOneSpaceRight, oppositeColorOfPiece)) {
        const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceRight) ;
        validMoves.push_back(Move(move, pieceColor, oneSpaceForwardOneSpaceRight) );
    }

    if (board->hasPieceAtPosition(oneSpaceForwardOneSpaceLeft, oppositeColorOfPiece)) {
        const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceLeft) ;
        validMoves.push_back(Move(move, pieceColor, oneSpaceForwardOneSpaceLeft)) ;
    }

    // en passant
    const auto pieceOnSquareToTheRight = board->pieceAtPosition(oneSpaceRight);

    if (pieceOnSquareToTheRight.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheRight.value(), oneSpaceRight, board->moveList)) {
        const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceRight) ;
        validMoves.push_back(Move(move, pieceColor, oneSpaceRight)) ;
    }

    const auto pieceOnSquareToTheLeft = board->pieceAtPosition(oneSpaceLeft);

    if (pieceOnSquareToTheLeft.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheLeft.value(), oneSpaceLeft, board->moveList)) {
        const auto move = std::make_pair(currentPosition, oneSpaceForwardOneSpaceLeft) ;
        validMoves.push_back(Move(move, pieceColor, oneSpaceLeft)) ;
    }

    return validMoves;
}

std::vector<Move> generateAllValidMovesForRook(const Board *board, const Position& current, const Piece *piece)  {
    const int row_difs[] = {-1, 1, 0, 0} ;
    const int col_difs[] = {0, 0, 1, -1} ;
    return generateMovesInStraightLine(board, current, piece->getColor(), row_difs, col_difs) ;
}



std::vector<Move> generateAllValidMovesForQueen(const Board *board, const Position& current, const Piece *piece)  {
    std::vector<Move> allValidMoves = {};
    auto allValidMovesForBishop = generateAllDiagonalMoves(board, current, piece->getColor());
    auto allValidMovesForRook = generateAllValidMovesForRook(board, current, piece) ;
    add_sets(allValidMoves, allValidMovesForBishop, allValidMovesForRook) ;
    return allValidMoves;
}


std::vector<Move> generateAllValidMovesForBishop(const Board *board, const Position& current, const Piece *piece)  {
    return generateAllDiagonalMoves(board, current, piece->getColor()) ;
}


std::vector<Move> generateMovesInStraightLine(const Board *board, const Position& currentPosition, PieceColor pieceColor, const int row_difs[], const int col_difs[])  {
    std::vector<Move> validMoves;
    PieceColor oppositePieceColor = opposite_color(pieceColor);

    for (int i = 0; i < 4; i++) {
        int row = currentPosition.row + row_difs[i] ;
        int col = currentPosition.col + col_difs[i] ;

        while (row >= 0 && col >= 0 && row < 8 && col < 8) {
            auto moveTo = Position(row, col) ;
            const auto move = std::make_pair(currentPosition, moveTo);

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

std::vector<Move> generateAllDiagonalMoves(const Board *board, const Position& current, PieceColor color)  {
    const int row_difs[] = {-1, -1, 1, 1} ;
    const int col_difs[] = {-1, 1, 1, -1} ;
    return generateMovesInStraightLine(board, current, color, row_difs, col_difs) ;
}




std::vector<Move> generateAllValidMovesForKing(const Board *board, const Position& currentPosition, const Piece *piece)  {
    std::vector<Move> validMoves;
    PieceColor pieceColor = piece->getColor() ;
    PieceColor oppositePieceColor = opposite_color(pieceColor);
    const int row_difs[] = {1, 1, 0, -1, -1, -1, 0, 1} ;
    const int col_difs[] = {0, 1, 1,  1,  0, -1, -1, -1} ;

    for (int i = 0; i < 8; i++) {
        auto row_dif = row_difs[i] ;
        auto col_dir = col_difs[i] ;
        auto moveTo = Position(currentPosition.row + row_dif, currentPosition.col + col_dir) ;
        const auto move = std::make_pair(currentPosition, moveTo);

        if (!board->hasPieceAtPosition(moveTo, pieceColor)) {
            if (board->hasPieceAtPosition(moveTo, oppositePieceColor)) {
                validMoves.push_back(Move(move,pieceColor, moveTo)) ;

            } else {
                validMoves.push_back(Move(move,pieceColor)) ;
            }
        }
    }

    if (!piece->hasMoved()) {
        if (pieceColor == PieceColor::WHITE) {
            auto leftCorner = Position{7, 0};

            if (board->unmovedRookAtPosition(leftCorner)) {
                bool uninterruptedPathToLeftRook = true;

                for (int i = currentPosition.col - 1; i > 0; i--) {
                    if (board->hasPieceAtPosition(Position{7, i})) {
                        uninterruptedPathToLeftRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToLeftRook) {
                    auto castleMoveKingDest = Position{7, 2};
                    auto castleMoveRookDest = Position{7, 3};
                    const auto king_move = std::make_pair(currentPosition, castleMoveKingDest);
                    const auto rook_move = std::make_pair(leftCorner, castleMoveRookDest);
                    validMoves.push_back(Move(king_move, pieceColor, rook_move));
                }
            }

            auto rightCorner = Position{7, 7};

            if (board->unmovedRookAtPosition(rightCorner)) {
                bool uninterruptedPathToRightRook = true;

                for (int i = currentPosition.col + 1; i < 7; i++) {
                    if (board->hasPieceAtPosition(Position{7, i})) {
                        uninterruptedPathToRightRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToRightRook) {
                    auto castleMoveKingDest = Position{7, 6};
                    auto castleMoveRookDest = Position{7, 5};
                    const auto king_move = std::make_pair(currentPosition, castleMoveKingDest);
                    const auto rook_move = std::make_pair(rightCorner, castleMoveRookDest);
                    validMoves.push_back(Move(king_move, pieceColor, rook_move));
                }
            }

        } else if (pieceColor == PieceColor::BLACK) {
            auto leftCorner = Position{0, 0};

            if (board->unmovedRookAtPosition(leftCorner)) {
                bool uninterruptedPathToLeftRook = true;

                for (int i = currentPosition.col - 1; i > 0; i--) {
                    if (board->hasPieceAtPosition(Position{0, i})) {
                        uninterruptedPathToLeftRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToLeftRook) {
                    auto castleMoveKingDest = Position{0, 2};
                    auto castleMoveRookDest = Position{0, 3};
                    const auto king_move = std::make_pair(currentPosition, castleMoveKingDest);
                    const auto rook_move = std::make_pair(leftCorner, castleMoveRookDest);
                    validMoves.push_back(Move(king_move, pieceColor,  rook_move));
                }
            }

            auto rightCorner = Position{0, 7};

            if (board->unmovedRookAtPosition(rightCorner)) {
                bool uninterruptedPathToRightRook = true;

                for (int i = currentPosition.col + 1; i < 7; i++) {
                    if (board->hasPieceAtPosition(Position{0, i})) {
                        uninterruptedPathToRightRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToRightRook) {
                    auto castleMoveKingDest = Position{0, 6};
                    auto castleMoveRookDest = Position{0, 5};
                    const auto king_move = std::make_pair(currentPosition, castleMoveKingDest);
                    const auto rook_move = std::make_pair(rightCorner, castleMoveRookDest);
                    validMoves.push_back(Move(king_move, pieceColor, rook_move));
                }
            }
        }
    }

    return validMoves ;
}

bool isPawnAndHasMovedOnceTwoSquaresForward(Piece *piece, Position piece_pos) {
    if (piece->getType() == PieceType::PAWN && piece->getTimesMoved() == 1) {
        auto pieceIsWhite = piece->getColor() == PieceColor::WHITE;
        return ((pieceIsWhite && piece_pos.row == 4) || (!pieceIsWhite && piece_pos.row==3)) ;
    }

    return false;
}

std::vector<Move> generateAllValidMovesForKnight(const Board *board, const Position& currentPosition, const Piece *piece)  {
    std::vector<Move> validMoves ;
    auto pieceColor = piece->getColor();
    auto oppositePieceColor = opposite_color(pieceColor);
    const int row_difs[] = {1, 1, -1, -1, 2, 2, -2, -2} ;
    const int col_difs[] = {2, -2, 2, -2, 1, -1, 1, -1} ;

    for (int i = 0; i < 8; i++) {
        auto row_dif = row_difs[i] ;
        auto col_dif = col_difs[i] ;
        auto moveTo = Position(currentPosition.row + row_dif, currentPosition.col + col_dif) ;
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
    }

    return validMoves;
}




