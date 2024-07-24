#include "board.h"
#include <memory>


using namespace std;
const int ROW = 8;
const int COL = 8;


  Board::Board() {
    auto board = make_unique<vector<vector<unique_ptr<Piece>>>>();
    board->resize(8);
    for (auto& row : *board) {
        row.resize(8);
    }
  }     // constructing a board;

  void Board::init() {
    //board = vector<vector<Piece>>(8, vector<Piece>(8));
    setupBoard();
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
      setBoard('p', "a7");
      setBoard('p', "b7");
      setBoard('p', "c7");
      setBoard('p', "d7");
      setBoard('p', "e7");
      setBoard('p', "f7");
      setBoard('p', "g7");
      setBoard('R', "a1");
      setBoard('R', "h1");
      setBoard('N', "b1");
      setBoard('N', "g1");
      setBoard('B', "c1");
      setBoard('B', "f1");
      setBoard('Q', "d1");
      setBoard('K', "e1");
      setBoard('P', "a2");
      setBoard('P', "h2");
      setBoard('P', "b2");
      setBoard('P', "g2");
      setBoard('P', "c2");
      setBoard('P', "f2");
      setBoard('P', "d2");
      setBoard('P', "e2");
      
      // set PAWN

    }
    void Board::setBoard(char piece, string coord) {
      
      int col = coord.at(0) - 'a';  // Convert 'a'-'h' to 0-7
      int row = 8 - stoi(coord.substr(1));

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
      int col = coord.at(0) - 'a';  // Convert 'a'-'h' to 0-7
      int row = 8 - stoi(coord.substr(1));
      (*board)[row][col] = nullptr;
    }
    // remove PIECE at current COORD:
Piece* Board::getPiece(const string &coord) const{
    // Extract the row and column from the coordinate string
    int col = coord.at(0) - 'a';  // Convert 'a'-'h' to 0-7
    int row = 8 - stoi(coord.substr(1));  // Convert '1'-'8' to 7-0 (assuming bottom-left is (0,0))

    // Return the piece at the given position (row, col)
    return (*board)[row][col].get();
}

    // return PIECE at COORD in BOARD
    void Board::undoLastMove() {

    }
    bool Board::isInCheck(bool white) const {
      if (white) {

      }

    }
    bool Board::isInCheckmate(bool white) const {
      
    }
    bool Board::isStalemate() const {

    }  // Checks if the game is in a stalemate
    //void setup();  // Sets up the board for a new game or custom setup

    void Board::display() {
      for (int row = 0; row < 8; ++row) {
        int curRow = 8 - row;  // Calculate the current row number in descending order
        cout << curRow << " ";  // Print the current row number
        for (const auto& cell : (*board)[row]) {
            if (cell) {
                cout << cell->getSymbol();
            } else {
                cout << "_";
            }
        }
        cout << endl;
    }

    cout << "  abcdefgh" << endl;
  }






// for player implementations:
map<string, char> Board::pieceCoords(bool isWhite) {
  // returns the coordinates of pieces left on board

} 


vector<map<string, int>> Board::possibleMoves(string coord) {
  // returns possible moves for piece
  // <coord, type (capture)>
  // maybe
  // checkmate -> 4
  // check -> 3
  // capture -> 2
  // normal -> 1

} 
map<map<string, char>, vector<map<string, int>>> Board::allMoves(bool isWhite) {
  // finds all possible moves and classifies

  
} // finds all possible moves and classifies

