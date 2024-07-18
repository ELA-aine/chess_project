#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite, char symbol);  // Constructor: Initializes Pawn with color
    bool isValidMove(const std::string &from, const std::string &to, const Board &board) const override;  // Overrides to check if the move is valid for a Pawn
    char getSymbol() const override;  // Provides the symbol for the Pawn

    bool isEnPassantMove(const std::string &from, const std::string &to, const Board &board) const;  // Checks if the move is an en passant capture
    void performEnPassant(const std::string &from, const std::string &to, Board &board);  // Executes the en passant capture
    void resetEnPassantStatus();  // Resets the en passant status

private:
    bool enPassantPossible;  // Flag to indicate if en passant is possible for this pawn
};

#endif // PAWN_H
