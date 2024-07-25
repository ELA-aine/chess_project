#include "board.h"

// Board are used to control all the behaviuors of the pieces and change the state accordingly

using namespace std;
const int ROW = 8;
const int COL = 8;


// Constructor of Board
Board::Board() {
  board.resize(8);
    for (auto &row : board) {
        row.resize(8);
    }
}     // constructing a board;

// initializing the board
void Board::init() {
  setupBoard();
} 
    
// setup the default board
void Board::setupBoard() {
    setBoard('N', "b1");
    setBoard('n', "b8");
    setBoard('N', "g1");
    setBoard('n', "g8");
    setBoard('B', "c1");
    setBoard('b', "c8");
    setBoard('B', "f1");
    setBoard('b', "f8");
    setBoard('Q', "d1");
    setBoard('q', "d8");
    setBoard('R', "a1");
    setBoard('r', "a8");
    setBoard('R', "h1");
    setBoard('r', "h8");
    setBoard('K', "e1");
    setBoard('k', "e8");
   for (int i = 0; i < 8; ++i) {
        board[1][i] = make_unique<Pawn>(false, 'p'); // Black pawns
        board[6][i] = make_unique<Pawn>(true, 'P');  // White pawns
    }
}

void Board::setBoard(char piece, string coord) {
    int row = 8 - (coord[1] - '0');
    int col = coord[0] - 'a';

    // Logic to convert char piece to actual Piece object
    // Example:
    switch (piece) {
        case 'P':
            board[row][col] = make_unique<Pawn>(true, 'P');
            break;
        case 'p':
            board[row][col] = make_unique<Pawn>(false, 'p');
            break;
        case 'N':
            board[row][col] = make_unique<Knight>(true, 'N');
            break;
        case 'n':
            board[row][col] = make_unique<Knight>(false, 'n');
            break;
        case 'B':
            board[row][col] = make_unique<Bishop>(true, 'B');
            break;
        case 'b':
            board[row][col] = make_unique<Bishop>(false, 'b');
            break;
        case 'Q':
            board[row][col] = make_unique<Queen>(true, 'Q');
            break;
        case 'q':
            board[row][col] = make_unique<Queen>(false, 'q');
            break;
        case 'R':
            board[row][col] = make_unique<Rook>(true, 'R');
            break;
        case 'r':
            board[row][col] = make_unique<Rook>(false, 'r');
            break;  
        case 'K':
            board[row][col] = make_unique<King>(true, 'K');
            break;
        case 'k':
            board[row][col] = make_unique<King>(false, 'k');
            break; 
        // Add other pieces here...
    }

}
    // set PIECE at COORD, replace if COORD already has a piece
    // restriction: pawn is not at first row or last row
    //              special piece can only appear once in the board
void Board::removePiece(string coord) {
  int row = 8 - (coord[1] - '0');
  int col = coord[0] - 'a';
  board[row][col] = nullptr;
}
    // remove PIECE at current COORD:
Piece* Board::getPiece(const string &coord) const{
    // Extract the row and column from the coordinate string
    /* int col = coord.at(0) - 'a';  // Convert 'a'-'h' to 0-7
    int row = 8 - stoi(coord.substr(1));  */ // Convert '1'-'8' to 7-0 (assuming bottom-left is (0,0))
    int row = 8 - (coord[1] - '0');
    int col = coord[0] - 'a';

    // Return the piece at the given position (row, col)
    
    return board[row][col].get();
}

void Board::changeBoard(const string &from, const string &to, char piece) {
    cout << "Change piece:" << piece << endl;
    setBoard(piece, to);
    removePiece(from);
}

void Board::display() {
    int count;
      for (int row = 0; row < 8; ++row) {
        int curRow = 8 - row;  // Calculate the current row number in descending order
        cout << curRow << " ";  // Print the current row number
        count = 0;
        for (const auto& cell : board[row]) {
            
            if (cell) {
                cout << cell->getSymbol();
            } else {
                if (count % 2 == 0) {
                    cout << "_";
                } else {
                    cout << " ";
                }
            }
            count++;
        }
        cout << endl;
    }
    cout << endl;
    cout << "  abcdefgh" << endl;
}

bool Board::checkValidMove(const string &from, const string &to) {
   auto movingPiece = getPiece(from);


    if (!movingPiece) {
        cout << "No piece at the starting position!" << endl;
        return false;
    }
    char pieceSymbol = movingPiece->getSymbol();

    auto destinationPiece = getPiece(to);
    
    // Check if the move is valid for the piece
    if (!movingPiece->isValidMove(from, to)) {
        cout << "Invalid move, move again" << endl;
        return false;
    }
    // If it's a piece that moves in a line, check if the path is clear

    
    if (pieceSymbol == 'B' || pieceSymbol == 'b' || pieceSymbol == 'R' || pieceSymbol == 'r' || pieceSymbol == 'Q' || pieceSymbol == 'q') {
        if (!isPathClear(from, to)) {
            cout << "Path is not clear!" << endl;
            return false;
        }
    }


    // Check if destination has a piece and handle capture
    if (destinationPiece) {
        if (destinationPiece->isWhite() == movingPiece->isWhite()) {
            cout << "Cannot capture your own piece!" << endl;
            return false;
        } else {
            cout << "Capture " << destinationPiece->getSymbol() << endl;
        }
    }

    // Perform the move
    //changeBoard(from, to, movingPiece->getSymbol());

    
    return true;
}



bool Board::isPathClear(const std::string &from, const std::string &to) const {     //Bishop
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    int dx, dy;

    if (endX > startX) {
        dx = 1;
    } else if (endX < startX) {
        dx = -1;
    } else {
        dx = 0;
    }

    if (endY > startY) {
        dy = 1;
    } else if (endY < startY) {
        dy = -1;
    } else {
        dy = 0;
    }

    int x = startX + dx;
    int y = startY + dy;


    while (x != endX && y != endY) {
        // Check if there's a piece on the current square
        auto piece = getPiece(std::string(1, 'a' + x) + std::to_string(y + 1));
        if (piece) {
            // If there's a piece and it's friendly, path is blocked
            if (piece->isWhite() == getPiece(from)->isWhite()) {
                return false;
            }
        }
        x += dx;
        y += dy;
    }

    return true;
}

bool Board::canPromote(const std::string &to) {
    int row = 8 - (to[1] - '0');
    return row == 7 || row == 0;
}

bool Board::isInCheck(bool white) const {
      string kingPosition;
      // this should be used in makeMove and isInCheck in game.h
      // check if the given white is in check
      // so parse through every piece on the board, and first find the numerical position of the king of bool. position should be in string format because the parameter of isValidMove function is string. 
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y){
          string currentCoord = string(1, 'a' + x) + to_string(y + 1); // this line produce alphabetical coordinates like 'e2', a5', 'f5'
          Piece *piece = getPiece(currentCoord);
          if(piece && piece->getSymbol() == (white ? 'K' : 'k')) {
            string kingPosition = currentCoord;
          }
        }
      } // parsing through every possible coordinate

      // once we have the position of the king, we could use isValidMove to all possible attacking moves, whether these would threaten the king
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y){
        string coord = string(1, 'a' + x) + to_string(y + 1);
         Piece *piece = getPiece(coord);
            if (piece && piece->isWhite() != white) {
                if (piece->isValidMove(coord, kingPosition, make_unique<Board>(*this))) {
                    return true; // The king is in check
                }
            }
        }
    }
} 

