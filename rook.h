#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(bool isWhite, char symbol);  // Constructor: Initializes Rook with color
    bool isValidMove(const std::string &from, const std::string &to, const Board &board) const override;  // Overrides to check if the move is valid for a Rook
    char getSymbol() const override;  // Provides the symbol for the Rook
};

#endif // ROOK_H
