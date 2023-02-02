#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "Board.hpp"
#include "Piece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "Position.hpp"

#include "chess_exceptions.cpp"


std::optional<Piece*> initial_piece(int row, int col) {
    bool isWhitePiece = row == 6 || row == 7;
    if (row == 0 || row == 7) {
        switch (col) {
        case 0:
            return new Rook(isWhitePiece) ;
        case 1:
            return new Knight(isWhitePiece) ;
        case 2:
            return new Bishop(isWhitePiece);
        case 3:
            return new Queen(isWhitePiece) ;
        case 4:
            return new King(isWhitePiece) ;
        case 5:
            return new Bishop(isWhitePiece);
        case 6:
            return new Knight(isWhitePiece) ;
        case 7:
            return new Rook(isWhitePiece) ;
        default:
            throw RuntimeError();
        }
    }
    if (row == 1 || row == 6) {
        return new Pawn(isWhitePiece);
    }
    return {};
}

Board::Board() {
    int initial_x_offset = 720;
    int initial_y_offset = 300;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            bool isWhite = (row + col) % 2 == 0;
            board[row][col] = new Square(isWhite, row, col, initial_x_offset + col * 50, initial_y_offset + row * 50, 50.f, initial_piece(row, col));
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            square->draw(target);
        }
    }
}



std::optional<Position> Board::getRowAndColOfMouse(const sf::Vector2f mousePos) const {
    for (const auto &row : board) {
        for (const auto &square : row) {
            if (square->getBoundaries().contains(mousePos)) {
                return square->getPosition();
            }
        }
    }
    return {};
}

bool pieceCanBeCapturedEnPassant(Piece *piece, Position position, const std::vector<Move> moveList) {
    if (piece->getType() == PieceType::PAWN && piece->getTimesMoved() == 1) {
        if ((piece->isWhite() && position.row == 6) || (!piece->isWhite() && position.row==3)) {
            if (moveList.back().moveTo == position) {
                return true ;
            }
            return false;
        }
    }
    return false;
}



std::set<Move> Board::generateAllValidMovesForPawn(const Position& current, const Piece *piece) const {
    std::set<Move> validMoves;
    bool isPieceWhite = piece->isWhite();
    bool oppositeColorOfPiece = !isPieceWhite;
    Position oneSpaceForward = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col) ;
    Position oneSpaceRight = Position(current.row, current.col +  (isPieceWhite ? 1  : - 1)) ;
    Position oneSpaceLeft = Position(current.row, current.col + (isPieceWhite ? -1 : 1)) ;
    Position oneSpaceForwardOneSpaceRight = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col + (isPieceWhite ? 1 : -1)) ;
    Position oneSpaceForwardOneSpaceLeft = Position(current.row +  (isPieceWhite ? - 1 : 1), current.col + (isPieceWhite ? -1 : 1)) ;
    if (!piece->hasMoved()) {
        Position twoSpacesForward = Position(current.row + (isPieceWhite ? - 2 : 2), current.col) ;
        if (!hasPieceAtPosition(twoSpacesForward)) {
            validMoves.insert({twoSpacesForward}) ;
        }
    }
    if (!hasPieceAtPosition(oneSpaceForward)) {
        validMoves.insert({oneSpaceForward})  ;
    }
    if (hasPieceAtPosition(oneSpaceForwardOneSpaceRight, oppositeColorOfPiece)) {
        validMoves.insert({oneSpaceForwardOneSpaceRight}) ;
    }
    if (hasPieceAtPosition(oneSpaceForwardOneSpaceLeft, oppositeColorOfPiece)) {
        validMoves.insert({oneSpaceForwardOneSpaceLeft}) ;
    }
    // en passant
    auto pieceOnSquareToTheRight = pieceAtPosition(oneSpaceRight);
    if (pieceOnSquareToTheRight.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheRight.value(), oneSpaceRight, this->moveList)) {
        validMoves.insert({oneSpaceForwardOneSpaceRight, oneSpaceRight}) ;
    }
    auto pieceOnSquareToTheLeft = pieceAtPosition(oneSpaceLeft);
    if (pieceOnSquareToTheLeft.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheLeft.value(), oneSpaceLeft, this->moveList)) {
        validMoves.insert({oneSpaceForwardOneSpaceLeft, oneSpaceLeft}) ;
    }
    return validMoves;
}

std::set<Move> Board::generateAllValidMovesForRook(const Position& current, const Piece *piece) const {
    std::set<Move> validMoves;
    bool pieceIsWhite = piece->isWhite();
    bool oppositeColorOfPiece = !pieceIsWhite;
    // moves down
    for (int row = current.row+1; row < 8; row++) {
        if (hasPieceAtPosition(row, current.col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, current.col), Position(row, current.col)}) ;
            break;
        } else if (hasPieceAtPosition(row, current.col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, current.col)}) ;
        }
    }
    // moves up
    for (int row = current.row-1; row >= 0; row--) {
        if (hasPieceAtPosition(row, current.col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, current.col), Position(row, current.col)}) ;
            break;
        } else if (hasPieceAtPosition(row, current.col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, current.col)}) ;
        }
    }
    for (int col = current.col-1; col >= 0; col--) {
        if (hasPieceAtPosition(current.row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(current.row, col), Position(current.row, col)}) ;
            break;
        } else if (hasPieceAtPosition(current.row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(current.row, col)}) ;
        }
    }
    for (int col = current.col+1; col < 8; col++) {
        if (hasPieceAtPosition(current.row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(current.row, col), Position(current.row, col)}) ;
            break;
        } else if (hasPieceAtPosition(current.row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(current.row, col)}) ;
        }
    }
    return validMoves;
}

template <typename T>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const std::set<T> &second_set) {
    result_set.insert(first_set.begin(), first_set.end());
    result_set.insert(second_set.begin(), second_set.end());
}

template <typename T, typename... Sets>
void add_sets(std::set<T> &result_set, const std::set<T> &first_set, const Sets&... sets) {
    add_sets(result_set, sets...);
    result_set.insert(first_set.begin(), first_set.end());
}


std::set<Move> Board::generateAllValidMovesForBishop(const Position& current, const Piece *piece) const {
    std::set<Move> allValidMoves = {};
    auto downAndLeft = generateValidMovesDownLeftDiagonal(current, piece->isWhite());
    auto downRight = generateValidMovesDownRightDiagonal(current, piece->isWhite());
    auto upAndRight = generateValidMovesUpRightDiagonal(current, piece->isWhite());
    auto upAndLeft = generateValidMovesUpLeftDiagonal(current, piece->isWhite());
    add_sets(allValidMoves, downAndLeft, downRight, upAndRight, upAndLeft);
    return allValidMoves;
}

std::set<Move> Board::generateValidMovesUpLeftDiagonal(const Position& current, bool pieceIsWhite) const {
    std::set<Move> validMoves;
    bool oppositeColorOfPiece = !pieceIsWhite;
    int row = current.row-1;
    int col = current.col-1;
    while (row >= 0 && col >= 0) {
        if (hasPieceAtPosition(row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, col), Position(row, col)}) ;
            break;
        } else if (hasPieceAtPosition(row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, col)}) ;
        }
        row -- ;
        col -- ;
    }
    return validMoves;
}

std::set<Move> Board::generateValidMovesUpRightDiagonal(const Position& current, bool pieceIsWhite) const {
    std::set<Move> validMoves;
    bool oppositeColorOfPiece = !pieceIsWhite;
    int row = current.row-1;
    int col = current.col+1;
    while (row >= 0 && col < 8) {
        if (hasPieceAtPosition(row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, col), Position(row, col)}) ;
            break;
        } else if (hasPieceAtPosition(row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, col)}) ;
        }
        row -- ;
        col ++ ;
    }
    return validMoves;
}

std::set<Move> Board::generateValidMovesDownRightDiagonal(const Position& current, bool pieceIsWhite) const {
    std::set<Move> validMoves;
    bool oppositeColorOfPiece = !pieceIsWhite;
    int row = current.row+1;
    int col = current.col+1;
    while (row < 8 && col < 8) {
        if (hasPieceAtPosition(row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, col), Position(row, col)}) ;
            break;
        } else if (hasPieceAtPosition(row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, col)}) ;
        }
        row ++ ;
        col ++ ;
    }
    return validMoves;
}

std::set<Move> Board::generateValidMovesDownLeftDiagonal(const Position& current, bool pieceIsWhite) const {
    std::set<Move> validMoves;
    bool oppositeColorOfPiece = !pieceIsWhite;
    int row = current.row+1;
    int col = current.col-1;
    while (row < 8 && col >= 0) {
        if (hasPieceAtPosition(row, col, oppositeColorOfPiece)) {
            validMoves.insert({Position(row, col), Position(row, col)}) ;
            break;
        } else if (hasPieceAtPosition(row, col, pieceIsWhite)) {
            break;
        } else {
            validMoves.insert({Position(row, col)}) ;
        }
        row ++ ;
        col -- ;
    }
    return validMoves;
}
bool positionInBoard(const Move &move) {
    auto pos = move.moveTo;
    return (pos.row >= 0 && pos.row < 8) && pos.col < 8 && pos.col >= 0;
}

void Board::processMove(const Position &coordinates_of_piece_to_move, const Move &requested_move) {
    if (requested_move.isCapture()) {
        removePieceFromSquare(requested_move.captures.value()) ;
    }
    this->move(coordinates_of_piece_to_move, requested_move.moveTo);
    this->moveList.push_back(requested_move) ;
}


std::set<Move> Board::generateAllValidMovesForPiece(const Position& current, const Piece *piece) const {
    std::set<Move> moves;
    if (piece->getType() == PieceType::PAWN) {
        moves = generateAllValidMovesForPawn(current, piece) ;
    }
    if (piece->getType() == PieceType::ROOK) {
        moves= generateAllValidMovesForRook(current, piece);
    }
    if (piece->getType() == PieceType::BISHOP) {
        moves = generateAllValidMovesForBishop(current, piece);
    }
    std::set<Move> validMoves;
    std::copy_if(moves.begin(), moves.end(), std::inserter(validMoves, validMoves.end()),  [](const Move & value) {
        return positionInBoard(value ) ;
    });
    return validMoves;
}


std::optional<Piece*> Board::pieceAtPosition(const Position& pos) const {
    if (!hasPieceAtPosition(pos)) {
        return {};
    }
    return this->squareAt(pos)->getPiece();
}

bool Board::hasPieceAtPosition(const Position& pos) const {
    std::optional<Piece*> piece;
    try {
        piece = this->squareAt(pos)->getPiece();
    } catch (const std::out_of_range& exp) {
        return false;
    }
    if (! piece.has_value() ) {
        return false;
    }
    return true;
}

bool Board::hasPieceAtPosition(const Position& pos, const bool targetColorIsWhite) const {
    return this->hasPieceAtPosition(pos.row, pos.col, targetColorIsWhite);
}

bool Board::hasPieceAtPosition(const size_t row, const size_t col, const bool targetColorIsWhite) const {
    std::optional<Piece*> piece;
    try {
        piece = this->squareAt(row, col)->getPiece();
    } catch (const std::out_of_range& exp) {
        return false;
    }
    if (! piece.has_value() ) {
        return false;
    }
    return piece.value()->isWhite() == targetColorIsWhite;
}


void Board::removePieceFromSquare(const Position& coordinates) {
    this->squareAt(coordinates)->removePiece();
}

Square* Board::squareAt(const Position& coord) const {
    return this->squareAt(coord.row, coord.col);
}

Square* Board::squareAt(size_t row, size_t col) const {
    return this->board.at(row).at(col);
}

void Board::move(const Position& current, const Position& destination) {
    std::optional<Piece*> userSelectedPiece = pieceAtPosition(current);
    if (!userSelectedPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }
    Piece *movingPiece = userSelectedPiece.value();
    removePieceFromSquare(current);
    this->squareAt(destination)->setPiece(movingPiece);
    movingPiece->setMoved();
}

void Board::setSquareColor(const Position &position, sf::Color color) {
    this->squareAt(position)->setColor(color) ;
}

void Board::resetAllSquaresColor() {
    for (auto &row : this->board) {
        for(auto &square : row) {
            square->setOriginalColor();
        }
    }
}



