#include "queen.h"


// Constructor: Initializes Queen with color
Queen::Queen(bool isWhite, char symbol) : Piece(isWhite, symbol) {}


// Overrides to check if the move is valid for a Queen
bool Queen::isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
   // Extract coordinates from strings
   int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
   int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
   int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
   int endY = to[1] - '1'; // Convert '1'-'8' to 0-7


   // Check if move is diagonal
   if (abs(startX - endX) == abs(startY - endY)) {
       return isPathClear(from, to, board);
   }


   // Check if move is horizontal
   if (startY == endY) {
       return isPathClear(from, to, board);
   }


   // Check if move is vertical
   if (startX == endX) {
       return isPathClear(from, to, board);
   }


   // If not diagonal, horizontal, or vertical, move is invalid
   return false;
}


// Provides the symbol for the Queen
char Queen::getSymbol() const {
   return isWhite ? 'Q' : 'q'; // 'Q' for white queen, 'q' for black queen
}


bool Queen::isPathClear(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
   int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
   int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
   int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
   int endY = to[1] - '1'; // Convert '1'-'8' to 0-7


   int dx = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
   int dy = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;


   int x = startX + dx;
   int y = startY + dy;


   while (x != endX || y != endY) {
       // Check if there's a piece on the current square
       auto piece = board->getPiece(std::string(1, 'a' + x) + std::to_string(y + 1));
       if (piece) {
           // If there's a piece and it's friendly, path is blocked
           if (piece->isWhite() == this->isWhite()) {
               return false;
           }
       }
       x += dx;
       y += dy;
   }


   // Check if the destination square is occupied by a friendly piece
   auto destinationPiece = board->getPiece(to);
   if (destinationPiece) {
       if (destinationPiece->isWhite() == this->isWhite()) {
           return false; // Cannot move to a square occupied by a friendly piece
       }
   }


   return true;
}
