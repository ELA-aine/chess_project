#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

  class Rook: public Piece {
    public:
      Rook(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif

// #ifndef ROOK_H
// #define ROOK_H

// #include "Piece.h"

// class Rook : public Piece {
// public:
//     Rook(bool isWhite);  // Constructor: Initializes Rook with color
//     bool isMoveValid(const std::string &from, const std::string &to, const Board &board) const override;  // Overrides to check if the move is valid for a Rook
// };

// #endif // ROOK_H
