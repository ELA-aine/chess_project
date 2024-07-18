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