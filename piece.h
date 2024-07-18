#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "board.h"
using namespace std;

class Piece {
  protected:
    bool white;
    char symbol;
  public:
    Piece(bool isWhite, char symbol);
    virtual bool isValidMove(const std::string &from, const std::string &to, const Board &board) const = 0; 
    // Pure virtual method to check if a move is valid
    virtual ~Piece() = default;
    virtual char getSymbol() const = 0;


};

#endif

