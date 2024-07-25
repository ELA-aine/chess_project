#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include "piece.h"
#include "pawn.h"
#include <iostream>
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "king.h"

using namespace std;

// purpose: To create a board
// Abstract Class


class Board {
  protected:
    vector<vector<unique_ptr<Piece>>> board;
    //vector<unique_ptr<Move>> moveHistory;

  public:
    Board();      // constructing a board;
    void init();    // initializing a board by putting all the necessary piece in *board
    void display();// (or ostream)
    // display/output the current board
    void setupBoard();
    void setBoard(char piece, string coord);
    // set PIECE at COORD, replace if COORD already has a piece
    // restriction: pawn is not at first row or last row
    //              special piece can only appear once in the board
    void removePiece(string coord);
    // remove PIECE at current COORD:
    Piece *getPiece(const string &coord) const;
    // return PIECE at COORD in BOARD
    

    // additional
    //void addMove(string from, string to, string piece, string promotion = "", string capture = "");

    void changeBoard(const string &from, const string &to, char piece);
    bool checkValidMove(const string &from, const string &to);
    bool isPathClear(const std::string &from, const std::string &to) const;
    bool canPromote(const std::string &to);
    bool isInCheck(bool white) const;
};


#endif
