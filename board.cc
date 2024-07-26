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

// Board::Board(const Board& other) {
//     // Deep copy of the board
//     board = std::make_unique<std::vector<std::vector<std::unique_ptr<Piece>>>>();
//     for (const auto& row : *other.board) {
//         std::vector<std::unique_ptr<Piece>> newRow;
//         for (const auto& piece : row) {
//             if (piece) {
//                 newRow.push_back(piece->clone());
//             } else {
//                 newRow.push_back(nullptr);
//             }
//         }
//         board->push_back(std::move(newRow));
//     }

//     // Copy the move history
//     tempMoveHistory = other.tempMoveHistory;
// }


void Board::init() {
  setupBoard();
} 
    
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

void Board::addMove(string from, string to, string piece, string promotion = "", string capture = "") {
  moveHistory.emplace_back(make_unique<Move>(from, to, piece, promotion, capture));
}


void Board::undoLastMove() {
  auto size = moveHistory.size();
  unique_ptr<Move> temp = move(moveHistory.at(size - 1));

  
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
          if(piece && piece ->getSymbol() == (white ? 'K' : 'k')) {
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
bool Board::isInCheckmate(bool white) const { // meaning no moves for king
        if (!isInCheck(white)) {
        // If the King is not in check, it cannot be in checkmate
        return false;
    }

      map<string, char> pieces = pieceCoords(white);

    // Iterate over each piece to find if there is any legal move.
    for (const auto &entry : pieces) {
        // Get the coordinate of the piece and its type.
        string coord = entry.first;
        char pieceType = entry.second;

        // Get all possible moves for the current piece.
        map<string, int> possibleMovesForPiece = possibleMoves(coord, white);

        // Check if there are any possible moves for this piece.
        if (!possibleMovesForPiece.empty()) {
            // If there are possible moves for any piece, it is not a stalemate.
            return false;
        }
    }
}

bool Board::isStalemate(bool white) const {
    if (isInCheck(white)) {
        return false;
    }

    map<string, char> pieces = pieceCoords(white);

    // Iterate over each piece to find if there is any legal move.
    for (const auto &entry : pieces) {
        // Get the coordinate of the piece and its type.
        string coord = entry.first;
        char pieceType = entry.second;

        // Get all possible moves for the current piece.
        map<string, int> possibleMovesForPiece = possibleMoves(coord, white);

        // Check if there are any possible moves for this piece.
        if (!possibleMovesForPiece.empty()) {
            // If there are possible moves for any piece, it is not a stalemate.
            return false;
        }
    }

    // If no legal moves are available and the king is not in check, it's a stalemate.
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

void Board::changeBoard(const string &from, const string &to, char piece) {
    cout << piece << endl;
    setBoard(piece, to);
    removeCoord(from);
}


// for player implementations:
map<string, char> Board::pieceCoords(bool isWhite) const {
  // returns the coordinates of pieces left on board
    map<string, char> pieceMap;
    
    // Iterate through each row of the board
    for (size_t row = 0; row < board->size(); ++row) {
      // Iterate through each column of the row
      for (size_t col = 0; col < (*board)[row].size(); ++col) {
        const auto& piece = (*board)[row][col];
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

// bool Pawn::isEnPassantMove(const std::string &from, const std::string &to, const Board &board) const {
//     int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
//     int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
//     int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
//     int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

//     if (!enPassantPossible) {
//         return false;
//     }

//     int direction = (this->isWhite()) ? 1 : -1;
//     if (endY == startY + direction && std::abs(endX - startX) == 1) {
//         auto adjacentPawn = board.getPiece(std::string(1, 'a' + endX) + std::to_string(startY));
//         if (adjacentPawn && adjacentPawn->getSymbol() == (this->isWhite() ? 'p' : 'P')) {
//             return true;
//         }
//     }

//     return false;
// }

bool Board::checkEnPassant(const std::string &fromCoord, const std::string &toCoord, bool isWhite) {
  

}

int Board::moveValue(const std::string &fromCoord, const std::string &toCoord, bool isWhite) const {
  Piece* fromPiece = getPiece(fromCoord);
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
  Piece *piece = getPiece(coord);
  map<string, int> moves;

  const int numMoves = 4;
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
  if (isValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // move 1 forward
  moveX = 'a' +  startX;
  moveY = to_string(direction + startY);
  toCoord = moveX + moveY;

  if (isValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // right diagonal
  moveX = 'a' + 1 + startX;
  moveY = to_string(direction + startY);
  if (isValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  // left diagonal
  moveX = 'a' - 1 + startX;
  moveY = to_string(direction + startY);
  if (isValidMove(coord, toCoord)) {
    moves[toCoord] = moveValue(coord, toCoord, isWhite);
  }

  return moves;

}

map<string, int> Board::getKnightMoves(string coord, bool isWhite) const {
  int startX = coord[0] - 'a'; // index X
  int startY = coord[1] - '1'; // index Y
  Piece *piece = getPiece(coord);
  map<string, int> moves;

  char moveX;
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
      if (isValidMove(coord, toCoord)) {
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
              if (isValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  if ((*board)[moveY][moveX]) break;
              }
          }
      }
  }

  return moves;


}

map<string, int> Board::getRookMoves(string coord, bool isWhite) const {
  map<string, int> moves;
  int startX = coord[0] - 'a';
  int startY = coord[1] - '1';

  const vector<pair<int, int>> moveOffsets = {
      {0, -1}, {0, 1}, {-1, 0}, {1, 0}
  };

  for (const auto& [dx, dy] : moveOffsets) {
      for (int i = 1; i < 8; ++i) {
          int moveX = startX + dx * i;
          int moveY = startY + dy * i;

          if (moveX >= 0 && moveX < 8 && moveY >= 0 && moveY < 8) {
              string toCoord = string(1, 'a' + moveX) + to_string(moveY + 1);
              if (isValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  if ((*board)[moveY][moveX]) break;
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
              if (isValidMove(coord, toCoord)) {
                  moves[toCoord] = moveValue(coord, toCoord, isWhite);
                  // Stop if there is a piece blocking the way
                  if ((*board)[moveY][moveX]) break;
              }
          }
      }
  }

  return moves;
}

map<string, int> Board::getKingMoves(string coord, bool isWhite) const {
  int direction = isWhite ? -1 : 1;
  int startX = coord[0] - 'a'; // index X
  int startY = coord[1] - '1'; // index Y
  Piece *piece = getPiece(coord);
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
            if (isValidMove(coord, toCoord)) {
                moves[toCoord] = moveValue(coord, toCoord, isWhite);
            }
        }
    }

  return moves;

}

map<string, int> Board::possibleMoves(string coord, bool isWhite) const {
  // returns possible moves for piece
  // <coord, type (capture)>
  // maybe
  // checkmate -> 4
  // check -> 3
  // capture -> 2
  // normal -> 1

  map<string, int> possibleMoves;
  // virtual Piece *getPiece(const string &coord)
  Piece *piece = getPiece(coord);

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
    possibleMoves = getRookMoves(coord, isWhite);
  } else if (symbol == 'q' || symbol == 'Q') {
    possibleMoves = getQueenMoves(coord, isWhite);
  } else if (symbol == 'k' || symbol == 'K') {
    possibleMoves = getKingMoves(coord, isWhite);
  }

  return possibleMoves;
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
    pieceMoves = possibleMoves(toCoord, isWhite);
    allMoves[toCoord] = pieceMoves;
  }

  return allMoves;
} // finds all possible moves and classifies


void Board::changeBoard(const string &from, const string &to, char piece) {
    cout << piece << endl;
    setBoard(piece, to);
    removeCoord(from);
}

// vector<Move> tempMoveHistory;
void Board::makeAMove(const string &from, const string &to, const string &promotion, bool isWhite) {
  Piece *piece = getPiece(from);
  Piece *capturedPiece = getPiece(to);

  string capture = capturedPiece ? string(1, capturedPiece->getSymbol()) : "";

  changeBoard(from, to, piece->getSymbol());

  Move move(from, to, isWhite, string(1, piece->getSymbol()), capture, promotion);
  tempMoveHistory.emplace_back(move);
}


void Board::undoMove(const string &from, const string &to, const string &promotion, bool isWhite) {
  Piece *piece = getPiece(from);
  Piece *capturedPiece = getPiece(to);

  string capture = capturedPiece ? string(1, capturedPiece->getSymbol()) : "";

  changeBoard(from, to, piece->getSymbol());

  auto val = tempMoveHistory.back(); // idk if i need to delete
  tempMoveHistory.pop_back();
}

void Board::changeBoard(const string &from, const string &to, char piece) {
    cout << piece << endl;
    setBoard(piece, to);
    removeCoord(from);
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

bool Board::isValidMove(const string &from, const string &to) const {
  auto movingPiece = getPiece(from);
    if (!movingPiece) {
        cout << "No piece at the starting position!" << endl;
        return false;
    }

    auto destinationPiece = getPiece(to);
    
    // Check if the move is valid for the piece
    if (!movingPiece->isValidMove(from, to)) {
        cout << "Invalid move, move again" << endl;
        return false;
    }

    // If it's a piece that moves in a line, check if the path is clear
    char pieceSymbol = movingPiece->getSymbol();
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

    return true;
}

bool Board::checkValidMove(const string &from, const string &to) {
  auto movingPiece = getPiece(from);
    if (!movingPiece) {
        cout << "No piece at the starting position!" << endl;
        return false;
    }

    auto destinationPiece = getPiece(to);
    
    // Check if the move is valid for the piece
    if (!movingPiece->isValidMove(from, to)) {
        cout << "Invalid move, move again" << endl;
        return false;
    }

    // If it's a piece that moves in a line, check if the path is clear
    char pieceSymbol = movingPiece->getSymbol();
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
    changeBoard(from, to, movingPiece->getSymbol());
    return true;
}



bool Board::isPathClear(const string &from, const string &to) const {     //Bishop
    int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
    int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
    int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
    int endY = to[1] - '1'; // Convert '1'-'8' to 0-7

    int dx = (endX > startX) ? 1 : -1;
    int dy = (endY > startY) ? 1 : -1;

    int x = startX + dx;
    int y = startY + dy;

    while (x != endX && y != endY) {
        // Check if there's a piece on the current square
        auto piece = getPiece(string(1, 'a' + x) + to_string(y + 1));
        if (piece) {
            // If there's a piece and it's friendly, path is blocked
            if (piece->isWhite() == getPiece(from)->isWhite()) {
                return false;
            }
        }
        x += dx;
        y += dy;
    }

    // Check if the destination square is occupied by a friendly piece
    auto destinationPiece = getPiece(to);
    if (destinationPiece) {
        if (destinationPiece->isWhite() == getPiece(from)->isWhite()) {
            return false; // Cannot move to a square occupied by a friendly piece
        }
    }

    return true;
}

bool Board::canPromote(const std::string &to) {
    int row = 8 - (to[1] - '0');
    return row == 7 || row == 0;
}
