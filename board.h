#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"

using namespace std;

// purpose: To create a board
// Abstract Class

class Board {
  vector<vector<Piece>> *board;         // creating a 8 * 8 board
  public:
    Board();      // constructing a board;
    virtual void init();    // initializing a board by putting all the necessary piece in *board
    virtual void display();// (or ostream)
    // display/output the current board
    virtual void setBoard(char piece, string coord);
    // set PIECE at COORD, replace if COORD already has a piece
    // restriction: pawn is not at first row or last row
    //              special piece can only appear once in the board
    virtual void removeCoord(string coord);
    // remove PIECE at current COORD:
    virtual void getPiece(string coord);
    // return PIECE at COORD in BOARD
};
   



