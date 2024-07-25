#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "move.h"
#include <memory>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"

class Piece;  // Forward declaration

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
    // Board(const Board& other);
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
    //void setup();  // Sets up the board for a new game or custom setup
    void changeBoard(const string &from, const string &to, char piece);
    // additional
    //void findPiece(char piece);
    void addMove(string from, string to, string piece, string promotion = "", string capture = "");
    bool checkValidMove(const string &from, const string &to);
    bool isPathClear(const std::string &from, const std::string &to) const;
    
    vector<Move> tempMoveHistory;
    void makeAMove(const string &from, const string &to, const string &promotion, bool isWhite);
    void undoMove(const string &from, const string &to, const string &promotion, bool isWhite);

    // for player implementation
    map<string, char> pieceCoords(bool isWhite) const; // returns the coordinates of pieces left on board 
    map<string, int> possibleMoves(string coord, bool isWhite) const; // returns possible moves for piece
    // <coord, type (capture)>
    // maybe
    // checkmate -> 4
    // check -> 3
    // capture -> 2
    // normal -> 1
    int moveValue(const std::string &fromCoord, const std::string &toCoord, bool isWhite)const ;
    map<string, int> getPawnMoves(string coord, bool isWhite) const;
    map<string, int> getKnightMoves(string coord, bool isWhite) const;
    map<string, int> getBishopMoves(string coord, bool isWhite) const;
    map<string, int> getRookMoves(string coord, bool isWhite) const;
    map<string, int> getQueenMoves(string coord, bool isWhite) const;
    map<string, int> getKingMoves(string coord, bool isWhite) const;


    map<string, map<string, int>> allMoves(bool isWhite) const; // finds all possible moves and classifies


};


#endif
