
#include "humanplayer.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player{isWhite} {}

std::string HumanPlayer::makeMove(std::unique_ptr<Board>& board, const std::string &from, 
    const std::string &to, const std::string &promotion) {

    bool canMove;
    string isCheck = "no"; // default to no

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
                canMove = movedPiece->isValidMove(from, to, board); // board is now a unique_ptr
            }

        } else { // white

            if (!isWhite) { // black
                canMove = false;
            } else {
                canMove = movedPiece->isValidMove(from, to, board);
            }

        }
        // check isCheck and isCheckMate,
    } else {
        canMove = false;
    }

    if (canMove) {
        return to + from + promotion + isCheck;
    } else {
        return "invalid move";
    }

}
