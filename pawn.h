#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

  class Pawn: public Piece {
    public:
      Pawn(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif