#ifndef KING_H
#define KING_H
#include <iostream>

#include "piece.h"

  class King: public Piece {
    public:
      King(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif

// #ifndef KING_H
// #define KING_H

// #include "Piece.h"

// class King : public Piece {
// public:
//     King(bool isWhite);  // Constructor: Initializes King with color
//     bool isMoveValid(const std::string &from, const std::string &to, const Board &board) const override;  // Overrides to check if the move is valid for a King
//     bool isInCheck(const Board &board) const;  // Checks if the King is in check

// private:
//     bool isCastling(const std::string &from, const std::string &to) const;  // Checks if the move is a castling move
// };

// #endif // KING_H
