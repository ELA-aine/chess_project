#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <memory>
#include <string>

class Board;

class King : public Piece {
public:
    // Constructor: Initializes King with color
    King(bool isWhite, char symbol = 'K');

    // Overrides to check if the move is valid for a King
    bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const override;

    // Provides the symbol for the King
    char getSymbol() const override;

    // Checks if castling is possible
    bool canCastle(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const;

        bool hasMoved() const; // Checks if the Rook has moved
    void setMoved(bool moved); // Sets the moved status of the Rook

private:
    bool isPathClear(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const;
    bool moved;
};

#endif // KING_H
