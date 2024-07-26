
#include "player.h"
#include <limits>
// for INT_MAX/MIN, max(), min()


#include "computerplayer.h"
using namespace std;


ComputerPlayer::ComputerPlayer(int level, bool isWhite) : Player{isWhite}, level{level} {}

bool ComputerPlayer::level1(std::unique_ptr<Board>& board, bool isWhite) {
    // random moves
    map<string, char> piecesLeft = board->pieceCoords(isWhite);

    // find from coord
    auto it = piecesLeft.begin();
    advance(it, rand() % piecesLeft.size());
    // take random from piecesLeft


    string fromCoord = it->first; 
    Piece* piece = board->getPiece(fromCoord);


    map<string, int> possibleMoves = board->possibleMoves(fromCoord, isWhite);
    auto jt = possibleMoves.begin();
    advance(jt, rand() % possibleMoves.size());

    string toCoord = jt->first;


    string promotion = "";

    // must meet promotion standards
    if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && board->canPromote(toCoord)) {
        // random promotion
        string promotionPossibilities[5] = {"queen", "rook", "knight", "bishop", ""};
        // possible pieces to be promoted to
        int index = (rand() % promotionPossibilities->length());
        promotion = promotionPossibilities[index];
    }

    // void changeBoard(const string &from, const string &to, char piece);
    board->changeBoard(fromCoord, toCoord, piece->getSymbol());
    return true;
    // (*board).getPiece(fromCoord)

}

bool ComputerPlayer::makeMove(std::unique_ptr<Board>& board, const std::string &from, const std::string &to, const std::string &promotion) {
    switch(level) {
        case 1:
            return level1(board, isWhite);
            break;
        /* case 2:
            return level2(board, isWhite);
            break;
        case 3:
            return level3(board, isWhite);
            break;
        case 4:
            int depth = 4; // CHANGE
            return level4(board, isWhite, depth);
            break; */
    }

    return "";
}






