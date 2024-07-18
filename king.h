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