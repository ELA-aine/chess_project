
#include "humanplayer.h"

HumanPlayer::HumanPlayer(bool isWhite) : Player{isWhite} {}

bool HumanPlayer::makeMove(std::unique_ptr<Board>& board, const std::string &from, 
    const std::string &to, const std::string &promotion) {
    cout << isWhite << endl;
    bool canMove;
    Piece* movedPiece = board->getPiece(from);
    char symbol = movedPiece->getSymbol(); 
    cout << symbol << endl;
    // or getColor() might work better

    if (movedPiece) { // check piece exists
        // check correct side
        if ('a' < symbol && symbol < 'z') { // black
            // getColor() might work better here
            if (isWhite) { // white
                canMove = false;
            } else {
                canMove = board->checkValidMove(from, to); // board is now a unique_ptr
            }

        } else { // white
            if (isWhite != true) { // black
                canMove = false;
            } else {
                canMove = board->checkValidMove(from, to);
            }

        }
        // check isCheck and isCheckMate,
    } else {
        canMove = false;
    }

    if (canMove) {
        if ((symbol == 'p' || symbol == 'P') && board->canPromote(to)) {
            char promotion;
            cout << "Pawn is ready for Promotion, Please enter the promoted piece: " << endl;
            cout << "r for Rook, b for Bishop, n for Knight, q for Queen if you are black, Capitalize them if you are white" << endl;
            cin >> promotion; 
            cout << "Your promotion choice is:" << promotion << endl;
            board->changeBoard(from, to, promotion);
        } else {
            board->changeBoard(from, to, symbol);
        }
        return true;
    } else {
        return false;
    }

}
