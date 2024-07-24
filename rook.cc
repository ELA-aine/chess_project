
#include "Rook.h"
#include "Board.h"
#include <cmath>

Rook::Rook(bool isWhite, char symbol) : Piece(isWhite, symbol), moved(false) {}

bool Rook::isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
    // Convert board coordinates from string to numeric
    int fromX = from[0] - 'a';
    int fromY = from[1] - '1';
    int toX = to[0] - 'a';
    int toY = to[1] - '1';

    // so a1 -> (0,0) b1 -> (1,0)

    // Check if move is horizontal or vertical
    if (fromX == toX || fromY == toY) {
        // Check if there are any pieces blocking the path
        // For horizontal moves
        if (fromY == toY) {
            int step = (toX > fromX) ? 1 : -1; // moving to right/ left
            for (int x = fromX + step; x != toX; x += step) {
                if (board->getPiece(std::string(1, 'a' + x) + std::to_string(fromY + 1))) {
                    return false; // There is a piece blocking the path
                }
            }
        }
        // For vertical moves
        else if (fromX == toX) {
            int step = (toY > fromY) ? 1 : -1;
            for (int y = fromY + step; y != toY; y += step) {
                if (board->getPiece(std::string(1, 'a' + fromX) + std::to_string(y + 1))) {
                    return false; // There is a piece blocking the path
                }
            }
        }

        // Check if destination is occupied by a friendly piece
        Piece* destPiece = board->getPiece(to);
        if (destPiece && destPiece->isWhite() == this->isWhite()) {
            return false; // Cannot move to a square occupied by a friendly piece
        } // because if it is opponent, this move is legit.

        return true; // The move is valid
    }

    return false; // The move is not horizontal or vertical
}


// Provides the symbol for the Rook
char Rook::getSymbol() const {
    return isWhite ? 'R' : 'r'; // 'Q' for white queen, 'q' for black queen
}

bool Rook::hasMoved() const {
    return moved;
}

void Rook::setMoved(bool moved) {
    this->moved = moved;
}
