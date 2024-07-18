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
   


// #ifndef BOARD_H
// #define BOARD_H

// #include <vector>
// #include <string>
// #include "Piece.h"
// #include "Move.h"

// class Board {
// public:
//     Board();  // Constructor: Initializes the Board object
//     void initialize();  // Sets up or resets the board to its initial state
//     void display() const;  // Displays the current state of the board
//     void movePiece(const std::string &from, const std::string &to, const std::string &promotion = "");  // Moves a piece on the board; optional promotion
//     void undoLastMove();  // Undoes the last move made on the board
//     bool isInCheck(bool white) const;  // Checks if the given color (white) is in check
//     bool isInCheckmate(bool white) const;  // Checks if the given color (white) is in checkmate
//     bool isStalemate() const;  // Checks if the game is in a stalemate
//     bool currentTurnIsWhite() const;  // Returns true if it's White's turn
//     void setup();  // Sets up the board for a new game or custom setup
    
// private:
//     std::vector<std::vector<Piece*>> board;  // 2D vector representing the board; stores pointers to Piece objects. not poitner because vecor already manages memory!!!
//     std::vector<Move> moveHistory;  // Vector of Move objects; keeps track of all moves made during the game
//     bool whiteTurn;  // Boolean flag to indicate if it's White's turn (true) or Black's turn (false)
//     void setupBoard();  // Helper method to initialize the board with pieces
// };

// #endif // BOARD_H
