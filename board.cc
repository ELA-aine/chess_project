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
    cout << coord << endl;
    cout << "111" << endl;
    cout << coord[0] << endl;
    // Extract the row and column from the coordinate string
    /* int col = coord.at(0) - 'a';  // Convert 'a'-'h' to 0-7
    int row = 8 - stoi(coord.substr(1));  */ // Convert '1'-'8' to 7-0 (assuming bottom-left is (0,0))
    int row = 8 - (coord[1] - '0');
    int col = coord[0] - 'a';
    cout << row << " " << col << endl;

    // Return the piece at the given position (row, col)
    Piece * piece2 = board[row][col].get();
    cout << "1212" << endl;
    return piece2;
}

void Board::changeBoard(const string &from, const string &to, char piece) {
    //out << "Change piece:" << piece << endl;
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

bool Board::checkValidMove(const string &from, const string &to) const {
   auto movingPiece = getPiece(from);


    if (!movingPiece) {
        // cout << "No piece at the starting position!" << endl;
        return false;
    }
    char pieceSymbol = movingPiece->getSymbol();

    auto destinationPiece = getPiece(to);
    
    // Check if the move is valid for the piece
    if (!movingPiece->isValidMove(from, to)) {
        // cout << "Invalid move, move again" << endl;
        return false;
    }
    // If it's a piece that moves in a line, check if the path is clear

    
    if (pieceSymbol == 'B' || pieceSymbol == 'b' || pieceSymbol == 'R' || pieceSymbol == 'r' || pieceSymbol == 'Q' || pieceSymbol == 'q') {
        if (!isPathClear(from, to)) {
            // cout << "Path is not clear!" << endl;
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

    cout << startX << startY << endX << endY << endl;
    bool isClear = true;

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
    cout << x << y << endl;


    while (true) {
        if (y == endY && x == endX) {
            break;
        }
        // cout << "this is x and y: " << x << ", " << y << endl;
        // Check if there's a piece on the current square
        auto piece = getPiece(std::string(1, 'a' + x) + std::to_string(y + 1));
        if (piece) {
            cout << piece->getSymbol() << endl;
           isClear = false;
           break;
        }

        if (x == endX && y != endY) {
            y += dy;
        } else if (y == endY && x != endX) {
            x += dx;
        } else if (y != endY && x != endX){
            x += dx;
            y += dy;
        } 
        
    }

    return isClear;
}

bool Board::canPromote(const std::string &to) {
    int row = 8 - (to[1] - '0');
    return row == 7 || row == 0;
}

bool Board::isInCheck(bool white) const {
    string kingPosition;

    // Find the position of the king
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            string currentCoord = string(1, 'a' + x) + to_string(y + 1);
            Piece *piece = getPiece(currentCoord);
            if (piece && piece->getSymbol() == (white ? 'K' : 'k')) {
                kingPosition = currentCoord;
                break; // Exit the loop once the king is found
            }
        }
        if (!kingPosition.empty()) break; // Exit the outer loop if the king is found
    }

    // Check if any opposing piece can attack the king
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            string coord = string(1, 'a' + x) + to_string(y + 1);
            Piece *piece = getPiece(coord);
            if (piece && piece->isWhite() != white) {
                if (piece->isValidMove(coord, kingPosition)) {
                    // For pieces that move in a line, check if the path is clear
                    char pieceSymbol = piece->getSymbol();
                    if (pieceSymbol == 'B' || pieceSymbol == 'b' || pieceSymbol == 'R' || pieceSymbol == 'r' || pieceSymbol == 'Q' || pieceSymbol == 'q') {
                        if (!isPathClear(coord, kingPosition)) {
                            continue; // Path is not clear, so this piece can't check the king
                        }
                    }
                    return true; // The king is in check
                }
            }
        }
    }

    cout << "The king is not in check" << endl;
    return false;
}

map<string, char> Board::pieceCoords(bool isWhite) const {
  // returns the coordinates of pieces left on board
    map<string, char> pieceMap;
    
    // Iterate through each row of the board
    for (size_t row = 0; row < board.size(); ++row) {
      // Iterate through each column of the row
      for (size_t col = 0; col < (board)[row].size(); ++col) {
        const auto& piece = (board)[row][col];
        if (piece && piece->isWhite() == isWhite) {
          string rows = to_string(row);
          string cols = to_string(col);
          string coord = rows + cols;
          pieceMap[coord] = piece->getSymbol();
        }
      }
    }
    
    return pieceMap;
}

map<string, int> Board::possibleMoves(string coord, bool isWhite) const {
  // returns possible moves for piece
  cout << coord << endl;

  cout << "8" << endl;
  // <coord, type (capture)>
  // maybe
  // checkmate -> 4
  // check -> 3
  // capture -> 2
  // normal -> 1

  map<string, int> possibleMoves;
  // virtual Piece *getPiece(const string &coord)
  Piece *piece = getPiece(coord);
  cout << piece->getSymbol() << endl;

  if (!piece) {
    return possibleMoves;
  }

  char symbol = piece->getSymbol();
  if (symbol == 'p' || symbol == 'P') {
    // pawn
    possibleMoves = getPawnMoves(coord, isWhite);
  } else if (symbol == 'n' || symbol == 'N') {
    possibleMoves = getKnightMoves(coord, isWhite);
  } else if (symbol == 'b' || symbol == 'B') {
    possibleMoves = getBishopMoves(coord, isWhite);
  } else if (symbol == 'r' || symbol == 'R') {
    cout << "9" << endl;
    possibleMoves = getRookMoves(coord, isWhite);
  } else if (symbol == 'q' || symbol == 'Q') {
    possibleMoves = getQueenMoves(coord, isWhite);
  } else if (symbol == 'k' || symbol == 'K') {
    possibleMoves = getKingMoves(coord, isWhite);
  }

  return possibleMoves;
} 

int Board::moveValue(const std::string &fromCoord, const std::string &toCoord, bool isWhite) const {
  //Piece* fromPiece = getPiece(fromCoord);
  Piece* toPiece = getPiece(toCoord);

  int value = 1;

  // if (isInCheckmate(!isWhite)) {
  //     value = 4; // checkmate
  // } else if (isInCheck(!isWhite)) {
  //     value = 3; // check
  // } else 
  
  if (toPiece && toPiece->isWhite() != isWhite) {
    value = 2; // capture
  }

  // No need to undo move, as we used a temporary board
  return value;
}


map<string, int> Board::getPawnMoves(string coord, bool isWhite) const {
  int direction = isWhite ? -1 : 1;
  int startX = coord[0] - 'a'; // index X
  int startY = coord[1] - '1'; // index Y
  //Piece *piece = getPiece(coord);
  map<string, int> moves;

  //const int numMoves = 4;
  // 2 forward
  // 1 forward
  // diagonal right
  // diagonal left
  char moveX;
  string moveY;
  string toCoord;

  // forward 2 spots
  moveX = 'a' +  startX;
  moveY = to_string((direction * 2) + startY);
  toCoord = moveX + moveY;

  // isValidMove(from, to, board)
  if (checkValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // move 1 forward
  moveX = 'a' +  startX;
  moveY = to_string(direction + startY);
  toCoord = moveX + moveY;

  if (checkValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // right diagonal
  moveX = 'a' + 1 + startX;
  moveY = to_string(direction + startY);
  if (checkValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // left diagonal
  moveX = 'a' - 1 + startX;
  moveY = to_string(direction + startY);
  if (checkValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  return moves;

}

map<string, int> Board::getKnightMoves(string coord, bool isWhite) const {
  int startX = coord[0] - 'a'; // index X
  int startY = coord[1] - '1'; // index Y
  //Piece *piece = getPiece(coord);
  map<string, int> moves;

  //char moveX;
  string moveY;
  string toCoord;

  const vector<pair<int, int>> moveOffsets = {
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
    {-2,  1}, {-1,  2}, {1,  2}, {2,  1}
  };

  for (const auto& [dx, dy] : moveOffsets) {
    int moveX = startX + dx;
    int moveY = startY + dy;

    if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
      string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
      if (checkValidMove(coord, toCoord)) {
        moves[toCoord] = moveValue(coord, toCoord, isWhite);
      }
    }
  }

  return moves;
}

map<string, int> Board::getBishopMoves(string coord, bool isWhite) const {
  map<string, int> moves;
  int startX = coord[0] - 'a';
  int startY = coord[1] - '1';

  const vector<pair<int, int>> moveOffsets = {
      {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
  };

  for (const auto& [dx, dy] : moveOffsets) {
      for (int i = 1; i < 8; ++i) {
          int moveX = startX + dx * i;
          int moveY = startY + dy * i;

          if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
              string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
              if (checkValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  if (board[moveY][moveX]) break;
              }
          }
      }
  }

  return moves;


}

map<string, int> Board::getRookMoves(string coord, bool isWhite) const {
  map<string, int> moves;
  cout << "6" << endl;
  int startX = coord[0] - 'a';
  int startY = coord[1] - '1';
  cout << "7" << endl;

  const vector<pair<int, int>> moveOffsets = {
      {0, -1}, {0, 1}, {-1, 0}, {1, 0}
  };

  for (const auto& [dx, dy] : moveOffsets) {
    
      for (int i = 1; i < 8; ++i) {
          int moveX = startX + dx * i;
          int moveY = startY + dy * i;
 
          if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
              string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
              if (checkValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  if (board[moveY][moveX]) break;
              }
          }
      }
  }

  return moves;
}

map<string, int> Board::getQueenMoves(string coord, bool isWhite) const {
  map<string, int> moves;
  int startX = coord[0] - 'a';
  int startY = coord[1] - '1';

  const vector<pair<int, int>> moveOffsets = {
      {-1, -1}, {0, -1}, {1, -1},
      {-1,  0},         {1,  0},
      {-1,  1}, {0,  1}, {1,  1},
      {-1, -1}, {0,  0}, {1,  1},
      { 0,  0}, {1, -1}, {0, -1},
      {1,  0}, {1,  1}, {0,  1}
  };

  for (const auto& [dx, dy] : moveOffsets) {
      for (int i = 1; i < 8; ++i) {
          int moveX = startX + dx * i;
          int moveY = startY + dy * i;

          if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
              string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
              if (checkValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  // Stop if there is a piece blocking the way
                  if (board[moveY][moveX]) break;
              }
          }
      }
  }

  return moves;
}

map<string, int> Board::getKingMoves(string coord, bool isWhite) const {
  //int direction = isWhite ? -1 : 1;
  int startX = coord[0] - 'a'; // index X
  int startY = coord[1] - '1'; // index Y
  //Piece *piece = getPiece(coord);
  map<string, int> moves;

  const vector<pair<int, int>> moveOffsets = {
    {-1, -1}, {0, -1}, {1, -1},
    {-1,  0},         {1,  0},
    {-1,  1}, {0,  1}, {1,  1}
  };

  for (const auto& [dx, dy] : moveOffsets) {
    int moveX = startX + dx;
    int moveY = startY + dy;

    if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
        string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
        if (checkValidMove(coord, toCoord)) {
            moves[toCoord] = moveValue(coord, toCoord, isWhite);
        }
    }
  }

  return moves;

}

map<string, map<string, int>> Board::allMoves(bool isWhite) const {
  // finds all possible moves and classifies
  // map<string, char> pieceCoords(bool isWhite)
  map<string, char> pieces = pieceCoords(isWhite);
  map<string, int> pieceMoves;
  map<string, map<string, int>> allMoves;
  string toCoord;
  // auto &it = pieces.begin();
  for (const auto &it : pieces) {
    toCoord = it.first;
    // toCoord 00
    cout << it.first;
    cout << it.second << endl;
    pieceMoves = possibleMoves(toCoord, isWhite);
    allMoves[toCoord] = pieceMoves;
  }

  return allMoves;
} // finds all possible moves and classifies

