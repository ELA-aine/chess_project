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
      std::string kingPosition;
      // this should be used in makeMove and isInCheck in game.h
      // check if the given white is in check
      // so parse through every piece on the board, and first find the numerical position of the king of bool. position should be in string format because the parameter of isValidMove function is string. 
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y){
          std::string currentCoord = std::string(1, 'a' + x) + std::to_string(y + 1); // this line produce alphabetical coordinates like 'e2', a5', 'f5'
          Piece *piece = getPiece(currentCoord);
          if(piece && piece ->getSymbol() == (white ? 'K' : 'k')) {
            string kingPosition = currentCoord;
          }
        }
      } // parsing through every possible coordinate

      // once we have the position of the king, we could use isValidMove to all possible attacking moves, whether these would threaten the king
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y){
        std::string coord = std::string(1, 'a' + x) + std::to_string(y + 1);
         Piece *piece = getPiece(coord);
            if (piece && piece->isWhite() != white) {
                if (piece->isValidMove(coord, kingPosition, std::make_unique<Board>(*this))) {
                    return true; // The king is in check
                }
            }
        }
    }
} 
    bool Board::isInCheckmate(bool white) const { // meaning no legals moves but is not in check.
      
    }
  bool Board::isStalemate(bool white) const {
    // Check if the player is in check
    if (isInCheck(white)) {
        return false;
    }

    // Get the coordinates of all pieces of the given color
    map<string, char> pieces = pieceCoords(white);

    // Iterate over all pieces
    for (const auto &entry : pieces) {
        string coord = entry.first;
        Piece *piece = getPiece(coord);

        // Get possible moves for the current piece
        vector<map<string, int>> moves = possibleMoves(coord); 

        // Check if there is at least one legal move
        for (const auto &move : moves) {
            // Create a temporary board to simulate the move
            auto tempBoard = make_unique<vector<vector<unique_ptr<Piece>>>>(*board);
            string targetCoord = move.begin()->first;
            Piece *targetPiece = getPiece(targetCoord);
            
            // Move the piece on the temporary board
            (*tempBoard)[targetCoord[1] - '1'][targetCoord[0] - 'a'] = move(board[coord[1] - '1'][coord[0] - 'a']); // fix later
            (*tempBoard)[coord[1] - '1'][coord[0] - 'a'].reset();

            // Check if the move leaves the player in check
            if (!isInCheck(white)) {
                return false; // There is at least one legal move
            }
        }
    }

    // If no legal moves are found, it's a stalemate
    return true;
}
 // meaning no legals moves but is not in check.
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
    