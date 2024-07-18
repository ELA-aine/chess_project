#ifndef PIECE_H
#define PIECE_H
#include <string>
using namespace std;

class Piece {
  protected:
    string colour;
    int curX, curY;
  public:
    Piece(string colour, int curX, int curY);
    virtual bool isValid(int endX, int endY);


};

#endif

/*
class Piece {
public:
    Piece(bool isWhite);          // Constructor to initialize a piece with its color
    virtual ~Piece() = default;   // Virtual destructor for proper cleanup
    bool isWhite() const;         // Method to check if the piece is white
    virtual char getSymbol() const = 0; // Pure virtual method to get the symbol of the piece
    virtual bool isValidMove(const std::string &from, const std::string &to, const Board &board) const = 0; // Pure virtual method to check if a move is valid
protected:
    bool white;   // Boolean to store if the piece is white
};
*/
