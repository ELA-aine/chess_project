#ifndef PIECE_H
#define PIECE_H

class Piece {
  protected:
    string colour;
    int curX, int curY;
  public:
    Piece(string colour, int curX, int curY);
    virtual bool isValid(int endX, int endY);


};

#endif