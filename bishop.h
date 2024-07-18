#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite, char symbol);  // Constructor: Initializes Bishop with color
    bool isValidMove(const std::string &from, const std::string &to, const Board &board) const override;  // Overrides to check if the move is valid for a Bishop
    char getSymbol() const override;  // Provides the symbol for the Bishop
};

#endif // BISHOP_H
