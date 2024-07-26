#include "king.h"
#include "rook.h"
#include <cmath>


// Constructor: Initializes King with color
King::King(bool isWhite, char symbol) : Piece(isWhite, symbol) {}


// Overrides to check if the move is valid for a King
bool King::isValidMove(const std::string &from, const std::string &to) const {
   // Extract coordinates from strings
   int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
   int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
   int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7
   int endY = to[1] - '1'; // Convert '1'-'8' to 0-7


   // Calculate the absolute difference between start and end positions
   int dx = std::abs(startX - endX);
   int dy = std::abs(startY - endY);

   // Check if the move is a valid king move (one square in any direction)
   if ((dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0)) {
       // Check if the destination square is occupied by a friendly piece
       return true;
   }


   // Check for castling
   /* if (canCastle(from, to, board)) {
       return true;
   } */


   // If not a valid king move or castling, move is invalid
   return false;
}


// Provides the symbol for the King
char King::getSymbol() const {
   return this->symbol; // 'K' for white king, 'k' for black king
}


// Checks if castling is possible
/* bool King::canCastle(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
   // Extract coordinates from strings
   int startX = from[0] - 'a'; // Convert 'a'-'h' to 0-7
   int startY = from[1] - '1'; // Convert '1'-'8' to 0-7
   int endX = to[0] - 'a'; // Convert 'a'-'h' to 0-7


   // Determine the rook's initial position based on the castling move
   std::string rookFrom;
   std::string rookTo;
   if (from == "e1" && to == "g1") { // White king-side castling
       rookFrom = "h1";
       rookTo = "f1";
   } else if (from == "e1" && to == "c1") { // White queen-side castling
       rookFrom = "a1";
       rookTo = "d1";
   } else if (from == "e8" && to == "g8") { // Black king-side castling
       rookFrom = "h8";
       rookTo = "f8";
   } else if (from == "e8" && to == "c8") { // Black queen-side castling
       rookFrom = "a8";
       rookTo = "d8";
   } else {
       return false; // Not a castling move
   }


   // // Check if the king or rook has moved
   // } --> Leave this to Elaine


   // Check if the path is clear between the king and rook
   if (!isPathClear(from, to, board)) {
       return false;
   }


   // // Check if the squares the king moves through are not under attack
   // for (int x = std::min(startX, endX); x <= std::max(startX, endX); ++x) {
   //     std::string square(1, 'a' + x);
   //     square += std::to_string(startY + 1);
   //     if (board->isSquareUnderAttack(square, !isWhite)) {
   //         return false;
   //     }
   // }


   return true;
}


bool King::isPathClear(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const {
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
           return false; // Path is blocked
       }
       x += dx;
       y += dy;
   }


   return true;
}


bool King::hasMoved() const {
   return moved;
}


void King::setMoved(bool moved) {
   this->moved = moved;
}
 */