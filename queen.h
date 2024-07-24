#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool isWhite, char symbol);  // Constructor: Initializes Queen with color
    bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const override;  // Overrides to check if the move is valid for a Queen
    char getSymbol() const override;  // Provides the symbol for the Queen

private:
    bool isPathClear(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const; // Private method to check if the path is clear
};

#endif // QUEEN_H
