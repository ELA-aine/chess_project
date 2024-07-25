#ifndef PIECE_H
#define PIECE_H




#include <string>
#include <memory> // For std::unique_ptr// For std::unique_ptr


class Board;  // Forward declaration

class Piece {
protected:
   bool white;
   char symbol;
public:
   Piece(bool isWhite, char symbol); // Constructor
   virtual bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const = 0; // Pure virtual method
   virtual ~Piece() = default;
   virtual char getSymbol() const = 0;
   bool isWhite() const { return white; }
   bool can_promote(string coord);
};


#endif // PIECE_H


