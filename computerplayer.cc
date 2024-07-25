
#include "player.h"
#include <limits>
// for INT_MAX/MIN, max(), min()


#include "computerplayer.h"
using namespace std;


ComputerPlayer::ComputerPlayer(int level, bool isWhite) : level{level}, isWhite{isWhite}, Player{isWhite} {}

bool ComputerPlayer::level1(std::unique_ptr<Board>& board, bool isWhite) {
    // random moves
    map<string, char> piecesLeft = (*board).pieceCoords(isWhite);

    // find from coord
    auto it = piecesLeft.begin();
    advance(it, rand() % piecesLeft.size());
    // take random from piecesLeft


    string fromCoord = it->first; 
    Piece* piece = (*board).getPiece(fromCoord);


    map<string, int> possibleMoves = (*board).possibleMoves(fromCoord, isWhite);
    auto jt = possibleMoves.begin();
    advance(jt, rand() % possibleMoves.size());

    string toCoord = jt->first;


    string promotion = "";

    // must meet promotion standards
    if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && piece->canPromote(fromCoord)) {
        // random promotion
        string promotionPossibilities[5] = {"queen", "rook", "knight", "bishop", ""};
        // possible pieces to be promoted to
        int index = (rand() % promotionPossibilities->length());
        promotion = promotionPossibilities[index];
    }

    // void changeBoard(const string &from, const string &to, char piece);
    (*board).changeBoard(fromCoord, toCoord, piece->getSymbol());
    return true;
    // (*board).getPiece(fromCoord)

}




bool ComputerPlayer::level2(std::unique_ptr<Board>& board, bool isWhite) {
    // prefers capturing moves and checks over other moves

    // map<string, map<string, int>> allMoves(bool isWhite) const; // finds all possible moves and classifies
    Board* temp = dynamic_cast<Board*>(board.get());

    map<string, map<string, int>> allMoves = temp->allMoves(isWhite);
    string from, to;
    map<string, string> moves;
    

    for (auto& pieceMoves : allMoves) {
        // pieceMoves.first : map<string, char>
        // pieceMoves.second : vector<map<string, int>>
        from = pieceMoves.first;

        map<string, int>& toCoords = pieceMoves.second;

        for (auto & coord : toCoords) {
            to = coord.first;
            if (coord.second > 1) {
                moves[from] = to;
            } 
        }

        
    }

    auto it = moves.begin();
    advance(it, rand() % moves.size());
    string fromCoord = it->first;
    string toCoord = it->second;

    Piece *piece = (*temp).getPiece(fromCoord);
    
    (*board).changeBoard(fromCoord, toCoord, piece->getSymbol());
    return true;

}

bool ComputerPlayer::level3(std::unique_ptr<Board>& board, bool isWhite) {
    // prefers avoiding capture, capturing moves, and checks

    Board* temp = dynamic_cast<Board*>(board.get());
    map<string, map<string, int>> allMovesOpp = temp->allMoves(!isWhite);
    string from, to;
    map<string, string> movesOpp;
    
    for (auto& pieceMoves : allMovesOpp) {
        // pieceMoves.first : map<string, char>
        // pieceMoves.second : vector<map<string, int>>
        from = pieceMoves.first;

        map<string, int>& toCoords = pieceMoves.second;

        for (auto & coord : toCoords) {
            to = coord.first;
            if (coord.second > 1) {
                movesOpp[from] = to;
            } 
        }

        
    }
    // movesOpp has all capture moves from opp <from, to>
    // map<from, to>
    // map<string, int> possibleMoves(string coord, bool isWhite) const;
    map<string, string> avoidCapture;
    map<string, int> avoidMove;
    string couldCapture, to;
    for (auto& pieceMoves : movesOpp) {
        couldCapture = pieceMoves.second;
        avoidMove = temp->possibleMoves(couldCapture, isWhite);
        for (auto &move : avoidMove) {
            if (move.second > 1){
                avoidCapture[couldCapture] = move.first;
            }
        }
    }

    auto it = avoidCapture.begin();
    advance(it, rand() % avoidCapture.size());
    string fromCoord = it->first;
    string toCoord = it->second;

    Piece *piece = (*temp).getPiece(fromCoord);

    (*board).changeBoard(fromCoord, toCoord, piece->getSymbol());
    return true;

}

int evaluateBoard(std::unique_ptr<Board>& board, bool isWhite) {

    if ((*board).isInCheckmate(isWhite)) {
        return isWhite ? -9999 : 9999;
        // replace with <limits> int min max
    } else if ((*board).isStalemate(isWhite)) {
        return 0;
    }

    map<char, int> values = {
        {'p', 1}, {'P', 1},
        {'k', 3}, {'K', 3},
        {'b', 3}, {'B', 3},
        {'r', 5}, {'R', 5},
        {'q', 9}, {'Q', 9}
    };

    // map<string, char> pieceCoords(bool isWhite);

    map<string, char> pieceWhite = (*board).pieceCoords(isWhite);
    map<string, char> pieceBlack = (*board).pieceCoords(!isWhite);

    int i = 0;
    int evaluated = 0;
    map<string, char> piece;
    auto it = pieceWhite.begin();

    for (it = pieceWhite.begin(); it != pieceWhite.end(); ++it) {
        evaluated += it->second;
    }

    for (it = pieceBlack.begin(); it != pieceBlack.end(); ++it) {
        evaluated -= it->second;
    }

    return evaluated;
}

int miniMax(std::unique_ptr<Board>& board, int depth, int alpha, int beta, bool isMaxPlayer, bool isWhite) {

    Board* temp = dynamic_cast<Board*>(board.get());

    if (depth == 0 || (*board).isStalemate(isWhite) 
        || (*board).isInCheckmate(isWhite) || (*board).isInCheckmate(!isWhite)) {
        return evaluateBoard(board, isWhite);
    }

    map<string, map<string, int>> allMovesWhite = temp->allMoves(isWhite);
    map<string, map<string, int>> allMovesBlack = temp->allMoves(!isWhite);

    // combine into one map
    map<string, map<string, int>> allMoves;
    allMoves.insert(allMovesWhite.begin(), allMovesWhite.end());
    allMoves.insert(allMovesBlack.begin(), allMovesBlack.end());
    //

    // combine, all
    auto it = allMoves.begin();
    string to, from;
    vector<pair<string, string>> moves;

    for (auto &move : allMoves) {
        from = move.first;
        map<string, int> toCoords = move.second;
        for (auto &to : toCoords) {
            pair<string, string> move = {from, to.first};
            moves.emplace_back(move);
        }
        
    }

    if (isMaxPlayer) {
        int maxEval = numeric_limits<int>::min();
        for (auto &it : moves) {
            
            (*board).makeAMove(it.first, it.second, "", isWhite);
            int eval = miniMax(board, depth - 1, alpha, beta, false, isWhite);
            (*board).undoMove(it.first, it.second, "", isWhite);

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);

            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        for (auto &it : moves) {
            (*board).makeAMove(it.first, it.second, "", isWhite);
            int eval = miniMax(board, depth - 1, alpha, beta, true, isWhite);
            (*board).undoMove(it.first, it.second, "", isWhite);
            minEval = min(minEval, eval);
            beta = min(beta, eval);

            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }

}

bool ComputerPlayer::level4(std::unique_ptr<Board>& board, bool isWhite, int depth) {
    // use alpha beta algorithm
    Board* temp = dynamic_cast<Board*>(board.get());
    //map<map<string, char>, map<string, int>> allMoves(bool isWhite);
    // <from, symbol>, <to, rank>

    string bestMoveTo, bestMoveFrom, promotion;
    int bestValue = numeric_limits<int>::min();
    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();

    // get legal moves
    map<string, map<string, int>> allMovesWhite = temp->allMoves(isWhite);
    map<string, map<string, int>> allMovesBlack = temp->allMoves(!isWhite);

    // combine into one map
    map<string, map<string, int>> allMoves;
    allMoves.insert(allMovesWhite.begin(), allMovesWhite.end());
    allMoves.insert(allMovesBlack.begin(), allMovesBlack.end());


    auto it = allMoves.begin();
    int boardValue;

    string to, from;
    vector<pair<string, string>> moves;

    for (auto &move : allMoves) {
        from = move.first;
        map<string, int> toCoords = move.second;
        for (auto &to : toCoords) {
            pair<string, string> move = {from, to.first};
            moves.emplace_back(move);
        }
        
    }

    for (auto &it : moves) {

        (*board).makeAMove(it.first, it.second, "", isWhite);
        boardValue = miniMax(board, depth - 1, alpha, beta, false, isWhite);
        (*board).undoMove(it.first, it.second, "", isWhite);

        if (boardValue > bestValue) {
            bestValue = boardValue;

            bestMoveTo = it.second; 
            bestMoveFrom = it.first; 
        }
    }

    Piece *piece = (*temp).getPiece(bestMoveFrom);
    (*board).changeBoard(bestMoveFrom, bestMoveTo, piece->getSymbol());
    return true;


}


bool ComputerPlayer::makeMove(std::unique_ptr<Board>& board, const std::string &from, const std::string &to, const std::string &promotion) {
    switch(level) {
        case 1:
            return level1(board, isWhite);
            break;
        case 2:
            return level2(board, isWhite);
            break;
        case 3:
            return level3(board, isWhite);
            break;
        case 4:
            int depth = 4; // CHANGE
            return level4(board, isWhite, depth);
            break;
    }

    return "";
}











