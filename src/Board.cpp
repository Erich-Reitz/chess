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
#include "move_generation.hpp"
#include "chess_exceptions.hpp"


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



bool Board::unmovedRookAtPosition(const Position &pos) const {
    const auto pieceAtSquare = pieceAtPosition(pos) ;

    if (pieceAtSquare.has_value()) {
        const auto piece = pieceAtSquare.value();
        return piece->getType() == PieceType::ROOK && !piece->hasMoved();
    }

    return false;
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
            if (valid_move.capturee.has_value() ) {
                if (valid_move.capturee.value() == positionOfColorKingWeAreConcernedAbout) {
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
    // now we want to see if black has a move to capture white's king
    // if it does, the previous move by white would place the king in check
    // and therefore be invalid
    return future_board.king_is_attacked(this->colorToMove) ;
}




void Board::processMove(const Move &move) {
    const auto currentColor = !this->colorToMove;

    if (move.isCapture()) {
        this->squareAt(move.capturee.value())->removePiece()  ;
    }

    if (move.isPawnPromotion()) {
        if (move.promoteTo == PieceType::QUEEN) {
            Piece *piece = new Piece(currentColor, PieceType::QUEEN ) ;
            removeAndSetPiece(piece, move.getOriginalSquare(), move.getDestination()) ;
        }

    } else if (move.isCastle()) {
        const auto current_pos = move.castlee.value().first;
        const auto dest = move.castlee.value().second;
        movePiece(current_pos, dest);

    } else {
        movePiece(move.getOriginalSquare(), move.getDestination());
    }

    this->moveList.push_back(move) ;
    this->colorToMove = opposite_color(this->colorToMove) ;
}

void Board::removeAndSetPiece(Piece* piece, const Position &currentPosition, const Position &destination) {
    this->squareAt(currentPosition)->removePiece();
    this->squareAt(destination)->setPiece(piece);
}

void Board::movePiece(const Position &currentPosition, const Position &destination) {
    std::optional<Piece*> userSelectedPiece = pieceAtPosition(currentPosition);

    if (!userSelectedPiece.has_value()) {
        throw CurrentSquareDoesNotContainPiece();
    }

    Piece *movingPiece = userSelectedPiece.value();
    removeAndSetPiece(movingPiece, currentPosition, destination);
    movingPiece->setMoved();
}


std::vector<Move> Board::generateAllValidMovesForPiece(const Position& current, const Piece *piece, bool careIfPlacesKingInCheck) const {
    std::vector<Move> moves = piece->generateAllMoves(this, current, piece) ;
    std::vector<Move> validMoves;
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





void Board::setSquareColor(const Position &position, sf::Color color) {
    // this->squareAt(position)->shape.set
}

void Board::resetAllSquaresColor() {
    // for (auto &row : this->board) {
    //     for(auto &square : row) {
    //         square->setOriginalColor();
    //     }
    // }
}



