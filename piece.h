#ifndef PIECE_H
#define PIECE_H
#include <string>
using namespace std;

class Piece {
  protected:
    string colour;
    int curX, curY;
  public:
    Piece(string colour, int curX, int curY);
    virtual bool isValid(int endX, int endY);


};

#endif