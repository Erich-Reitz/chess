#include <optional>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include "Board.hpp"
#include "Piece.hpp"
#include "Position.hpp"


#include "add_sets.cpp"
#include "chess_exceptions.cpp"

PieceColor opposite_color(PieceColor color) {
    return color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE ;
}

std::optional<Piece*> initial_piece(int row, int col) {
    bool isWhitePiece = row == 6 || row == 7;

    if (row == 0 || row == 7) {
        switch (col) {
        case 0:
            return new Piece(isWhitePiece, PieceType::ROOK) ;

        case 1:
            return new Piece(isWhitePiece, PieceType::KNIGHT) ;

        case 2:
            return new Piece(isWhitePiece, PieceType::BISHOP) ; 

        case 3:
            return new Piece(isWhitePiece, PieceType::QUEEN) ; 

        case 4:
            return new Piece(isWhitePiece, PieceType::KING) ; 

        case 5:
            return new Piece(isWhitePiece, PieceType::BISHOP) ; 

        case 6:
            return new Piece(isWhitePiece, PieceType::KNIGHT) ;

        case 7:
            return new Piece(isWhitePiece, PieceType::ROOK) ;

        default:
            throw RuntimeError();
        }
    }

    if (row == 1 || row == 6) {
        return new Piece(isWhitePiece, PieceType::PAWN);
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

Board::Board(const Board& rhs) {
    *this = rhs;
}

Board& Board::operator=(const Board& rhs) {
    this->colorToMove = rhs.colorToMove ;
    moveList = rhs.moveList;
    board.resize(8);

    for (int i = 0; i < 8; i++) {
        board[i].resize(8);

        for (int j = 0; j < 8; j++) {
            board[i][j] = new Square(*rhs.board[i][j]);
        }
    }

    return *this ;
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

bool isPawnAndHasMovedOnceTwoSquaresForward(Piece *piece, Position piece_pos) {
    if (piece->getType() == PieceType::PAWN && piece->getTimesMoved() == 1) {
        auto pieceIsWhite = piece->getColor() == PieceColor::WHITE;
        return ((pieceIsWhite && piece_pos.row == 4) || (!pieceIsWhite && piece_pos.row==3)) ;
    }

    return false;
}



bool pieceCanBeCapturedEnPassant(Piece *piece_to_be_captured, Position piece_pos, const std::vector<Move> &moveList) {
    return (isPawnAndHasMovedOnceTwoSquaresForward(piece_to_be_captured, piece_pos) && moveList.back().moveTo == piece_pos) ;
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

std::set<Move> Board::generateAllValidMovesForKing(const Position& currentPosition, const Piece *piece) const {
    std::set<Move> validMoves;
    PieceColor pieceColor = piece->getColor() ;
    PieceColor oppositePieceColor = opposite_color(pieceColor);
    const int row_difs[] = {1, 1, 0, -1, -1, -1, 0, 1} ;
    const int col_difs[] = {0, 1, 1,  1,  0, -1, -1, -1} ;

    for (int i = 0; i < 8; i++) {
        auto row_dif = row_difs[i] ;
        auto col_dir = col_difs[i] ;
        auto moveTo = Position(currentPosition.row + row_dif, currentPosition.col + col_dir) ;

        if (!hasPieceAtPosition(moveTo, pieceColor)) {
            if (hasPieceAtPosition(moveTo, oppositePieceColor)) {
                validMoves.insert(Move{currentPosition, moveTo, pieceColor, moveTo}) ;

            } else {
                validMoves.insert(Move{currentPosition, moveTo, pieceColor}) ;
            }
        }
    }

    if (!piece->hasMoved()) {
        if (pieceColor == PieceColor::WHITE) {
            auto leftCorner = Position{7, 0};

            if (unmovedRookAtPosition(leftCorner)) {
                bool uninterruptedPathToLeftRook = true;

                for (int i = currentPosition.col - 1; i > 0; i--) {
                    if (hasPieceAtPosition(Position{7, i})) {
                        uninterruptedPathToLeftRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToLeftRook) {
                    auto castleMoveKingDest = Position{7, 2};
                    auto castleMoveRookDest = Position{7, 3};
                    validMoves.insert(Move{currentPosition, castleMoveKingDest, pieceColor, {}, leftCorner, castleMoveRookDest});
                }
            }

            auto rightCorner = Position{7, 7};

            if (unmovedRookAtPosition(rightCorner)) {
                bool uninterruptedPathToRightRook = true;

                for (int i = currentPosition.col + 1; i < 7; i++) {
                    if (hasPieceAtPosition(Position{7, i})) {
                        uninterruptedPathToRightRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToRightRook) {
                    auto castleMoveKingDest = Position{7, 6};
                    auto castleMoveRookDest = Position{7, 5};
                    validMoves.insert(Move{currentPosition, castleMoveKingDest, pieceColor, {}, rightCorner, castleMoveRookDest});
                }
            }

        } else if (pieceColor == PieceColor::BLACK) {
            auto leftCorner = Position{0, 0};

            if (unmovedRookAtPosition(leftCorner)) {
                bool uninterruptedPathToLeftRook = true;

                for (int i = currentPosition.col - 1; i > 0; i--) {
                    if (hasPieceAtPosition(Position{0, i})) {
                        uninterruptedPathToLeftRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToLeftRook) {
                    auto castleMoveKingDest = Position{0, 2};
                    auto castleMoveRookDest = Position{0, 3};
                    validMoves.insert(Move{currentPosition, castleMoveKingDest, pieceColor, {}, leftCorner, castleMoveRookDest});
                }
            }

            auto rightCorner = Position{0, 7};

            if (unmovedRookAtPosition(rightCorner)) {
                bool uninterruptedPathToRightRook = true;

                for (int i = currentPosition.col + 1; i < 7; i++) {
                    if (hasPieceAtPosition(Position{0, i})) {
                        uninterruptedPathToRightRook = false;
                        break;
                    }
                }

                if (uninterruptedPathToRightRook) {
                    auto castleMoveKingDest = Position{0, 6};
                    auto castleMoveRookDest = Position{0, 5};
                    validMoves.insert(Move{currentPosition, castleMoveKingDest, pieceColor, {}, rightCorner, castleMoveRookDest});
                }
            }
        }
    }

    return validMoves ;
}

bool Board::unmovedRookAtPosition(const Position &pos) const {
    const auto pieceAtSquare = pieceAtPosition(pos) ;

    if (pieceAtSquare.has_value()) {
        const auto piece = pieceAtSquare.value();
        return piece->getType() == PieceType::ROOK && !piece->hasMoved();
    }

    return false;
}

std::set<Move> Board::generateAllValidMovesForPawn(const Position& currentPosition, const Piece *piece) const {
    std::set<Move> validMoves;
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

        if (!hasPieceAtPosition(oneSpaceForward) && !hasPieceAtPosition(twoSpacesForward) ) {
            validMoves.insert(Move{currentPosition, twoSpacesForward, pieceColor}) ;
        }
    }

    if (!hasPieceAtPosition(oneSpaceForward)) {
        validMoves.insert(Move{currentPosition, oneSpaceForward, pieceColor})  ;
    }

    if (hasPieceAtPosition(oneSpaceForwardOneSpaceRight, oppositeColorOfPiece)) {
        validMoves.insert(Move{currentPosition, oneSpaceForwardOneSpaceRight, pieceColor, oneSpaceForwardOneSpaceRight}) ;
    }

    if (hasPieceAtPosition(oneSpaceForwardOneSpaceLeft, oppositeColorOfPiece)) {
        validMoves.insert(Move{currentPosition, oneSpaceForwardOneSpaceLeft, pieceColor, oneSpaceForwardOneSpaceLeft}) ;
    }

    // en passant
    const auto pieceOnSquareToTheRight = pieceAtPosition(oneSpaceRight);

    if (pieceOnSquareToTheRight.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheRight.value(), oneSpaceRight, this->moveList)) {
        validMoves.insert(Move{currentPosition, oneSpaceForwardOneSpaceRight, pieceColor, oneSpaceRight}) ;
    }

    const auto pieceOnSquareToTheLeft = pieceAtPosition(oneSpaceLeft);

    if (pieceOnSquareToTheLeft.has_value() && pieceCanBeCapturedEnPassant(pieceOnSquareToTheLeft.value(), oneSpaceLeft, this->moveList)) {
        validMoves.insert(Move{currentPosition, oneSpaceForwardOneSpaceLeft, pieceColor, oneSpaceLeft}) ;
    }

    return validMoves;
}

std::set<Move> Board::generateAllValidMovesForRook(const Position& current, const Piece *piece) const {
    const int row_difs[] = {-1, 1, 0, 0} ;
    const int col_difs[] = {0, 0, 1, -1} ;
    return generateMovesInStraightLine(current, piece->getColor(), row_difs, col_difs) ;
}


std::set<Move> Board::generateAllValidMovesForQueen(const Position& current, const Piece *piece) const {
    std::set<Move> allValidMoves = {};
    auto allValidMovesForBishop = generateAllDiagonalMoves(current, piece->getColor());
    auto allValidMovesForRook = generateAllValidMovesForRook(current, piece) ;
    add_sets(allValidMoves, allValidMovesForBishop, allValidMovesForRook) ;
    return allValidMoves;
}


std::set<Move> Board::generateAllValidMovesForBishop(const Position& current, const Piece *piece) const {
    return generateAllDiagonalMoves(current, piece->getColor()) ;
}


std::set<Move> Board::generateMovesInStraightLine(const Position& currentPosition, PieceColor pieceColor, const int row_difs[], const int col_difs[]) const {
    std::set<Move> validMoves;
    PieceColor oppositePieceColor = opposite_color(pieceColor);

    for (int i = 0; i < 4; i++) {
        int row = currentPosition.row + row_difs[i] ;
        int col = currentPosition.col + col_difs[i] ;

        while (row >= 0 && col >= 0 && row < 8 && col < 8) {
            auto moveTo = Position(row, col) ;

            if (hasPieceAtPosition(moveTo, oppositePieceColor)) {
                // capture move
                validMoves.insert(Move{currentPosition, moveTo, pieceColor, moveTo}) ;
                break;

            } else if (hasPieceAtPosition(moveTo, pieceColor)) {
                // blocked by same color
                break;

            } else {
                validMoves.insert(Move{currentPosition, moveTo, pieceColor}) ;
            }

            row += row_difs[i] ;
            col += col_difs[i]  ;
        }
    }

    return validMoves;
}

std::set<Move> Board::generateAllDiagonalMoves(const Position& current, PieceColor color) const {
    const int row_difs[] = {-1, -1, 1, 1} ;
    const int col_difs[] = {-1, 1, 1, -1} ;
    return generateMovesInStraightLine(current, color, row_difs, col_difs) ;
}

bool positionInBoard(const Position &pos)  {
    return (pos.row >= 0 && pos.row < 8) && pos.col < 8 && pos.col >= 0;
}

std::set<std::pair<Position, Piece*>> Board::getAllPieces(PieceColor searchColor) const {
    std::set<std::pair<Position, Piece*>> pieces;

    for (int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8; j++) {
            if (squareAt(i, j)->getPiece().has_value()) {
                auto piece = squareAt(i, j)->getPiece().value() ;
                auto pos = Position(i, j)  ;
                auto pieceInfo = std::make_pair(pos, piece) ;

                if (searchColor == piece->getColor()) {
                    pieces.insert(pieceInfo);
                }
            }
        }
    }

    return pieces;
}

std::pair<Position, Piece*> Board::getKing(PieceColor color) const {
    for (int i = 0; i < 8 ; i++) {
        for (int j = 0; j < 8; j++) {
            if (squareAt(i, j)->getPiece().has_value()) {
                auto piece = squareAt(i, j)->getPiece().value() ;
                auto pos = Position(i, j)  ;
                auto pieceInfo = std::make_pair(pos, piece) ;

                if (color == piece->getColor() && piece->getType() == PieceType::KING) {
                    return pieceInfo ;
                }
            }
        }
    }
}



bool Board::king_is_attacked(PieceColor colorKingWeAreConcernedAbout) const {
    const auto positionOfColorKingWeAreConcernedAbout = getKing(colorKingWeAreConcernedAbout).first ;
    const auto opposite_color_of_king_we_are_concerned_about = opposite_color(colorKingWeAreConcernedAbout) ;
    const auto all_pieces = getAllPieces(opposite_color_of_king_we_are_concerned_about) ;

    for (auto piece : all_pieces) {
        auto allValidMoves = generateAllValidMovesForPiece(piece.first, piece.second, false) ;

        for (auto valid_move : allValidMoves) {
            if (valid_move.captures.has_value() ) {
                if (valid_move.captures.value() == positionOfColorKingWeAreConcernedAbout) {
                    return true;
                }
            }
        }
    }

    return false;
}

PieceColor Board::getColorToMove() const {
    return this->colorToMove;
}

bool Board::moves_finishes_with_king_in_check(const Move &move) const {
    // after we process move, no pieces should have a valid move to attack king
    Board future_board = *this;
    // if white, we are processing white's move
    future_board.processMove(move) ;
    // know we want to see if black has a move to capture white's king
    // if it does, the previous move by white would place the king in check
    // and therefore be invalid
    return future_board.king_is_attacked(this->colorToMove) ;
}

bool Board::legal_move(const Move &move, bool careIfPlacesKingInCheck) const {
    if (careIfPlacesKingInCheck) {
        return positionInBoard(move.moveTo) && !moves_finishes_with_king_in_check(move) ;
    }

    return positionInBoard(move.moveTo) ;
}

void Board::processMove(const Move &requested_move) {
    if (requested_move.isCapture()) {
        this->squareAt(requested_move.captures.value())->removePiece()  ;
    }

    this->move(requested_move.moveFrom, requested_move.moveTo);

    if (requested_move.alsoMoveFrom.has_value()) {
        if (!requested_move.alsoMoveTo.has_value()) {
            throw RuntimeError();
        }

        this->move(requested_move.alsoMoveFrom.value(), requested_move.alsoMoveTo.value());
    }

    this->moveList.push_back(requested_move) ;
    this->colorToMove = opposite_color(this->colorToMove) ;
}

std::set<Move> Board::generateAllValidMovesForKnight(const Position& currentPosition, const Piece *piece) const {
    std::set<Move> validMoves ;
    auto pieceColor = piece->getColor();
    auto oppositePieceColor = opposite_color(pieceColor);
    const int row_difs[] = {1, 1, -1, -1, 2, 2, -2, -2} ;
    const int col_difs[] = {2, -2, 2, -2, 1, -1, 1, -1} ;

    for (int i = 0; i < 8; i++) {
        auto row_dif = row_difs[i] ;
        auto col_dif = col_difs[i] ;
        auto moveTo = Position(currentPosition.row + row_dif, currentPosition.col + col_dif) ;

        if (!hasPieceAtPosition(moveTo, pieceColor)) {
            if (hasPieceAtPosition(moveTo, oppositePieceColor)) {
                // capture
                validMoves.insert(Move{currentPosition, moveTo, pieceColor, moveTo}) ;

            } else {
                // empty space
                validMoves.insert(Move{currentPosition, moveTo, pieceColor}) ;
            }
        }
    }

    return validMoves;
}


std::set<Move> Board::generateAllValidMovesForPiece(const Position& current, const Piece *piece, bool careIfPlacesKingInCheck) const {
    std::set<Move> moves = piece->generateAllValidMoves(current, *this) ;
    std::set<Move> validMoves;
    std::copy_if(moves.begin(), moves.end(), std::inserter(validMoves, validMoves.end()),  [&](const Move & move) {
        return  legal_move(move, careIfPlacesKingInCheck) ;
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

    return piece.has_value();
}

bool Board::hasPieceAtPosition(const Position& pos, const PieceColor target_color) const {
    std::optional<Piece*> piece;

    try {
        piece = this->squareAt(pos)->getPiece();

    } catch (const std::out_of_range& exp) {
        return false;
    }

    if (! piece.has_value() ) {
        return false;
    }

    return piece.value()->getColor() == target_color;
}


Square* Board::squareAt(const Position& coord) const {
    return this->board.at(coord.row).at(coord.col);
}


Square* Board::squareAt(int row, int col) const {
    return this->board.at(row).at(col);
}

void Board::move(const Position& current, const Position& destination) {
    std::optional<Piece*> userSelectedPiece = pieceAtPosition(current);

    if (!userSelectedPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }

    Piece *movingPiece = userSelectedPiece.value();
    this->squareAt(current)->removePiece();
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



