#include "Pawn.h"
#include "Board.h"
#include <cmath> // For std::abs

// Constructor: Initializes Pawn with color and symbol
Pawn::Pawn(bool isWhite, char symbol) : Piece(isWhite, symbol), enPassantPossible(false) {}

// Provides the symbol for the Pawn
char Pawn::getSymbol() const {
    return this->symbol; // Use the symbol provided at initialization
}

// Overrides to check if the move is valid for a Pawn
bool Pawn::isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    int direction = (this->isWhite()) ? 1 : -1; // 1 for white pawn, -1 for black pawn

    // Standard move: One step forward
    if (endX == startX && endY == startY + direction && !board->getPiece(to)) {
        return true;
    }

    // Initial move: Two steps forward
    if (endX == startX && endY == startY + 2 * direction && !board->getPiece(to) && 
        ((this->isWhite() && startY == 1) || (!this->isWhite() && startY == 6))) {
        return !board->getPiece(std::string(1, 'a' + startX) + std::to_string(startY + direction));
    }

    // Capture move: Diagonal move with a piece to capture
    if (std::abs(endX - startX) == 1 && endY == startY + direction) {
        auto destinationPiece = board->getPiece(to);
        if (destinationPiece && destinationPiece->isWhite() != this->isWhite()) {
            return true;
        }

        // En passant move
        if (isEnPassantMove(from, to, *board)) {
            return true;
        }
    }

    return false;
}

// Checks if the move is an en passant capture
bool Pawn::isEnPassantMove(const std::string &from, const std::string &to, const Board &board) const {
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    if (!enPassantPossible) {
        return false;
    }

    int direction = (this->isWhite()) ? 1 : -1;
    if (endY == startY + direction && std::abs(endX - startX) == 1) {
        auto adjacentPawn = board.getPiece(std::string(1, 'a' + endX) + std::to_string(startY));
        if (adjacentPawn && adjacentPawn->getSymbol() == (this->isWhite() ? 'p' : 'P')) {
            return true;
        }
    }

    return false;
}

// // Executes the en passant capture
// void Pawn::performEnPassant(const std::string &from, const std::string &to, Board &board) {
//     int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
//     int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
//     int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
//     int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

//     if (isEnPassantMove(from, to, board)) {
//         board.removeCoord(std::string(1, 'a' + endX) + std::to_string(startY)); // Remove the captured pawn
//         .makeMove(from, to); // Move the current pawn to the target square
//         resetEnPassantStatus(); // Reset the en passant status
//     }  
// }  [note!!] --> this should be implemented as a method in game, that should be used by makemove

// Resets the en passant status
void Pawn::resetEnPassantStatus() {
    enPassantPossible = false;
}
