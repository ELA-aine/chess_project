#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

  class Knight: public Piece {
    public:
      Knight(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif