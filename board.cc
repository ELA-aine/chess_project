#include "board.h"
#include <memory>


using namespace std;
const int ROW = 8;
const int COL = 8;

// purpose: To create a board
// Abstract Class


  //vector<vector<Piece>> *board;         // creating a 8 * 8 board
  //vector<Move> moveHistory;

  Board::Board() {
    board = make_unique<vector<vector<unique_ptr<Piece>>>>(8, vector<unique_ptr<Piece>>(8));
  }     // constructing a board;

  void Board::init() {
    //board = vector<vector<Piece>>(8, vector<Piece>(8));
    setup();
  }   // initializing a board by putting all the necessary piece in *board
    
    void Board::setupBoard() {
      setBoard('r', "a8");
      setBoard('r', "h8");
      setBoard('n', "b8");
      setBoard('n', "g8");
      setBoard('b', "c8");
      setBoard('b', "f8");
      setBoard('q', "d8");
      setBoard('k', "e8");
      // set pawn
      

      setBoard('R', "a8");
      setBoard('R', "h8");
      setBoard('N', "b8");
      setBoard('N', "g8");
      setBoard('B', "c8");
      setBoard('B', "f8");
      setBoard('Q', "d8");
      setBoard('K', "e8");
      // set PAWN

    }
    void Board::setBoard(char piece, string coord) {
      coordinate['a'] = 0;
      coordinate['b'] = 1;
      coordinate['c'] = 2;
      coordinate['d'] = 3;
      coordinate['e'] = 4;
      coordinate['f'] = 5;
      coordinate['g'] = 6;
      coordinate['h'] = 7;
      int row = coordinate.at(coord.at(0));
      int col = stoi(coord) - 1;

      switch(piece) {
        case 'K': 
          (*board)[row][col] = make_unique<King>(true, 'K'); 
          break;
        case 'k': 
          (*board)[row][col] = make_unique<King>(false, 'k'); 
          break;
        case 'Q': 
          (*board)[row][col] = make_unique<Queen>(true, 'Q'); 
          break;
        case 'q': 
          (*board)[row][col] = make_unique<Queen>(false, 'q'); 
          break;
        case 'R': 
          (*board)[row][col] = make_unique<Rook>(true, 'R'); 
            break;
        case 'r': 
          (*board)[row][col] = make_unique<Rook>(false, 'r'); 
          break;
        case 'B': 
          (*board)[row][col] = make_unique<Bishop>(true, 'B'); 
            break;
        case 'b': 
          (*board)[row][col] = make_unique<Bishop>(false, 'b'); 
          break;
        case 'N': 
          (*board)[row][col] = make_unique<Knight>(true, 'N'); 
          break;
        case 'n': 
          (*board)[row][col] = make_unique<Knight>(false, 'n'); 
          break;
        case 'P': 
          (*board)[row][col] = make_unique<Pawn>(true, 'P'); 
          break;
        case 'p': 
          (*board)[row][col] = make_unique<Pawn>(false, 'p'); 
          break;
        default: break;
    }

    }
    // set PIECE at COORD, replace if COORD already has a piece
    // restriction: pawn is not at first row or last row
    //              special piece can only appear once in the board
    void Board::removeCoord(string coord) {
      int row = coordinate.at(coord.at(0));
      int col = stoi(coord) - 1;
      (*board)[row][col] = nullptr;
    }
    // remove PIECE at current COORD:
    Piece *Board::getPiece(string coord){

    }
    // return PIECE at COORD in BOARD
    void Board::undoLastMove() {

    }
    bool Board::isInCheck(bool white) const {

    }
    bool Board::isInCheckmate(bool white) const {
      
    }
    bool isStalemate() const;  // Checks if the game is in a stalemate
    bool currentTurnIsWhite() const;  // Returns true if it's White's turn
    //void setup();  // Sets up the board for a new game or custom setup

    void Board::display() {
      for (auto it = board->begin(); it != board->end(); it++) {

      }
    }
    