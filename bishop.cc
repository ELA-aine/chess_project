#include "Bishop.h"
#include "Board.h"
#include <cmath> // For std::abs

// Constructor: Initializes Bishop with color
Bishop::Bishop(bool isWhite, char symbol) : Piece(isWhite, symbol) {}

// Overrides to check if the move is valid for a Bishop
bool Bishop::isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
    // Extract coordinates from strings
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    // Check if move is diagonal
    if (std::abs(startX - endX) == std::abs(startY - endY)) {
        return isPathClear(from, to, board);
    }

    // If not diagonal, move is invalid
    return false;
}

// Provides the symbol for the Bishop
char Bishop::getSymbol() const {
    return 'B'; // Standard symbol for Bishop
}

// Checks if the path is clear for the Bishop's move
bool Bishop::isPathClear(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    int dx = (endX > startX) ? 1 : -1;
    int dy = (endY > startY) ? 1 : -1;

    int x = startX + dx;
    int y = startY + dy;

    while (x != endX && y != endY) {
        // Check if there's a piece on the current square
        auto piece = board->getPiece(std::string(1, 'a' + x) + std::to_string(y + 1));
        if (piece) {
            // If there's a piece and it's friendly, path is blocked
            if (piece->isWhite() == this->isWhite()) {
                return false;
            }
        }
        x += dx;
        y += dy;
    }

    // Check if the destination square is occupied by a friendly piece
    auto destinationPiece = board->getPiece(to);
    if (destinationPiece) {
        if (destinationPiece->isWhite() == this->isWhite()) {
            return false; // Cannot move to a square occupied by a friendly piece
        }
    }

    return true;
}
