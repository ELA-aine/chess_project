#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory> // For std::unique_ptr
#include "board.h"

class Piece {
protected:
    bool white; 
    char symbol;
public:
    Piece(bool isWhite, char symbol); // Constructor
    virtual bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const = 0; // Pure virtual method
    virtual ~Piece() = default;
    virtual char getSymbol() const = 0;
    bool isWhite() const { return white; }
};

#endif // PIECE_H
