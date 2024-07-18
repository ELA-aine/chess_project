#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

  class Bishop: public Piece {
    public:
      Bishop(string colour, int curX, int curY);
      bool isValid(int endX, int endY);
  };

#endif