#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory> // For std::unique_ptr// For std::unique_ptr
//#include "board.h"

using namespace std;

class Board;

class Piece {
protected:
   bool white;
   char symbol;
public:
   Piece(bool isWhite, char symbol); // Constructor
   virtual bool isValidMove(const std::string &from, const std::string &to) const = 0; // Pure virtual method
   virtual ~Piece() = default;
   virtual char getSymbol() const = 0;
   bool isWhite() const { return white; }
   bool can_promote(string coord);
};


#endif // PIECE_H


