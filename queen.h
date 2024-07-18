#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

  class Queen: public Piece {
    public:
      Queen(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif