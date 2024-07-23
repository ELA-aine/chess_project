
#include "humanplayer.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player{isWhite} {}

std::string HumanPlayer::makeMove(Board *board, const std::string &from, const std::string &to, const std::string &promotion) {
    // read in to, from, promotion
    bool canMove;

    Piece* movedPiece = board->getPiece(from);
    char symbol = movedPiece->getSymbol(); 
    // or getColor() might work better



    if (movedPiece) { // check piece exists
        // check correct side
        if ('a' < symbol && symbol < 'z') { // black
            // getColor() might work better here
            if (isWhite) { // white
                canMove = false;
            } else {
                canMove = movedPiece->isValidMove(from, to, *board);
            }

        } else { // white

            if (!isWhite) { // black
                canMove = false;
            } else {
                canMove = movedPiece->isValidMove(from, to, *board);
            }

        }
    } else {
        canMove = false;
    }

    if (canMove) {
        return to + from + promotion;
    } else {
        return "invalid move";
    }

}
