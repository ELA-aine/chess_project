#ifndef BOARD_H
#define BOARD_H
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
#include "move.h"
#include <memory>

using namespace std;

// purpose: To create a board
// Abstract Class

class Board {
  protected:
    unique_ptr<vector<vector<unique_ptr<Piece>>>> board;
    //<vector<vector<Piece>>> *board;         // creating a 8 * 8 board
    vector<unique_ptr<Move>> moveHistory;

  public:
    Board();      // constructing a board;
    virtual void init();    // initializing a board by putting all the necessary piece in *board
    virtual void display();// (or ostream)
    // display/output the current board
    void setupBoard();
    virtual void setBoard(char piece, string coord);
    // set PIECE at COORD, replace if COORD already has a piece
    // restriction: pawn is not at first row or last row
    //              special piece can only appear once in the board
    virtual void removeCoord(string coord);
    // remove PIECE at current COORD:
    virtual Piece *getPiece(const string &coord) const;
    // return PIECE at COORD in BOARD
    void undoLastMove();  // Undoes the last move made on the board
    bool isInCheck(bool white) const;  // Checks if the given color (white) is in check
    bool isInCheckmate(bool white) const;  // Checks if the given color (white) is in checkmate
    bool isStalemate(bool white) const;  // Checks if the game is in a stalemate 
    //bool currentTurnIsWhite() const;  // Returns true if it's White's turn
    void setup();  // Sets up the board for a new game or custom setup

    // additional
    void findPiece(char piece);
    void addMove(string from, string to, string piece, string promotion = "", string capture = "");



    // for player implementation
    map<string, char> pieceCoords(bool isWhite) const; // returns the coordinates of pieces left on board 
    map<string, int> possibleMoves(string coord) const; // returns possible moves for piece
    // <coord, type (capture)>
    // maybe
    // checkmate -> 4
    // check -> 3
    // capture -> 2
    // normal -> 1
    map<map<string, char>, map<string, int>> allMoves(bool isWhite) const; // finds all possible moves and classifies
    map<string, string> tempMoveHistory;
    void makeAMove(string);
    void undoMove(string);

};


#endif
