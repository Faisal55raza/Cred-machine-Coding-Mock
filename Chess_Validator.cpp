#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class ChessBoard {
public:
    vector<vector<string>> chessboard;

    ChessBoard() {
        chessboard = {
            {"BR", "BN", "BB", "BQ", "BK", "BB", "BN", "BR"},
            {"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP"},
            {"WR", "WN", "WB", "WQ", "WK", "WB", "WN", "WR"}
        };
    }

    void printChessBoard() {
        for (const vector<string>& row : chessboard) {
            for (const string& cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
};

class BlackPieceMover {
private:
    ChessBoard &board;

    bool MoveBlackPawn(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int initialRow = 1;
        if (StartColNo == EndColNo && EndRowNo == StartRowNo + 1 && board.chessboard[EndRowNo][EndColNo] == "--") {
            return true;
        }
        if (StartRowNo == initialRow && StartColNo == EndColNo && EndRowNo == StartRowNo + 2 && board.chessboard[EndRowNo][EndColNo] == "--") {
            return true;
        }
        if ((StartColNo - 1 == EndColNo || StartColNo + 1 == EndColNo) && StartRowNo + 1 == EndRowNo && board.chessboard[EndRowNo][EndColNo] != "--") {
            return true;
        }
        return false;
    }

    bool MoveBlackRook(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        if (StartRowNo == EndRowNo || StartColNo == EndColNo) {
            return true;
        }
        return false;
    }

    bool MoveBlackKnight(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int rowDiff = abs(StartRowNo - EndRowNo);
        int colDiff = abs(StartColNo - EndColNo);
        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    }

    bool MoveBlackBishop(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        return abs(StartRowNo - EndRowNo) == abs(StartColNo - EndColNo);
    }

    bool MoveBlackKing(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int rowDiff = abs(StartRowNo - EndRowNo);
        int colDiff = abs(StartColNo - EndColNo);
        return rowDiff <= 1 && colDiff <= 1;
    }

    bool MoveBlackQueen(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        return (StartRowNo == EndRowNo || StartColNo == EndColNo) ||
               (abs(StartRowNo - EndRowNo) == abs(StartColNo - EndColNo));
    }

public:
    BlackPieceMover(ChessBoard& board) : board(board) {}

    bool Move(const string& StartMove, const string& EndMove) {
        int StartColNo = int(StartMove[0] - 'a');
        int StartRowNo = int(7 - (StartMove[1] - '1'));
        int EndColNo = int(EndMove[0] - 'a');
        int EndRowNo = int(7 - (EndMove[1] - '1'));

        if (StartColNo < 0 || StartColNo > 7 || EndColNo < 0 || EndColNo > 7 ||
            StartRowNo < 0 || StartRowNo > 7 || EndRowNo < 0 || EndRowNo > 7) {
            return false;
        }

        string pieceAtPosStart = board.chessboard[StartRowNo][StartColNo];
        if (pieceAtPosStart[0] == 'W' || pieceAtPosStart == "--") {
            return false;
        }

        if (pieceAtPosStart[1] == 'P') {
            if (MoveBlackPawn(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BP";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'R') {
            if (MoveBlackRook(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BR";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'N') {
            if (MoveBlackKnight(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BN";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'B') {
            if (MoveBlackBishop(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BB";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'K') {
            if (MoveBlackKing(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BK";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'Q') {
            if (MoveBlackQueen(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "BQ";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        }

        return false;
    }
};

class WhitePieceMover {
private:
    ChessBoard &board;

    bool MoveWhitePawn(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int initialRow = 6;
        if (StartColNo == EndColNo && EndRowNo == StartRowNo - 1 && board.chessboard[EndRowNo][EndColNo] == "--") {
            return true;
        }
        if (StartRowNo == initialRow && StartColNo == EndColNo && EndRowNo == StartRowNo - 2 && board.chessboard[EndRowNo][EndColNo] == "--") {
            return true;
        }
        if ((StartColNo - 1 == EndColNo || StartColNo + 1 == EndColNo) && StartRowNo - 1 == EndRowNo && board.chessboard[EndRowNo][EndColNo] != "--") {
            return true;
        }
        return false;
    }

    bool MoveWhiteRook(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        if (StartRowNo == EndRowNo || StartColNo == EndColNo) {
            return true;
        }
        return false;
    }

    bool MoveWhiteKnight(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int rowDiff = abs(StartRowNo - EndRowNo);
        int colDiff = abs(StartColNo - EndColNo);
        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    }

    bool MoveWhiteBishop(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        return abs(StartRowNo - EndRowNo) == abs(StartColNo - EndColNo);
    }

    bool MoveWhiteKing(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        int rowDiff = abs(StartRowNo - EndRowNo);
        int colDiff = abs(StartColNo - EndColNo);
        return rowDiff <= 1 && colDiff <= 1;
    }

    bool MoveWhiteQueen(int StartRowNo, int StartColNo, int EndRowNo, int EndColNo) {
        return (StartRowNo == EndRowNo || StartColNo == EndColNo) ||
               (abs(StartRowNo - EndRowNo) == abs(StartColNo - EndColNo));
    }

public:
    WhitePieceMover(ChessBoard& board) : board(board) {}

    bool Move(const string& StartMove, const string& EndMove) {
        int StartColNo = int(StartMove[0] - 'a');
        int StartRowNo = int(7 - (StartMove[1] - '1'));
        int EndColNo = int(EndMove[0] - 'a');
        int EndRowNo = int(7 - (EndMove[1] - '1'));

        if (StartColNo < 0 || StartColNo > 7 || EndColNo < 0 || EndColNo > 7 ||
            StartRowNo < 0 || StartRowNo > 7 || EndRowNo < 0 || EndRowNo > 7) {
            return false;
        }

        string pieceAtPosStart = board.chessboard[StartRowNo][StartColNo];
        if (pieceAtPosStart[0] == 'B' || pieceAtPosStart == "--") {
            return false;
        }

        if (pieceAtPosStart[1] == 'P') {
            if (MoveWhitePawn(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WP";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'R') {
            if (MoveWhiteRook(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WR";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'N') {
            if (MoveWhiteKnight(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WN";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'B') {
            if (MoveWhiteBishop(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WB";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'K') {
            if (MoveWhiteKing(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WK";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        } else if (pieceAtPosStart[1] == 'Q') {
            if (MoveWhiteQueen(StartRowNo, StartColNo, EndRowNo, EndColNo)) {
                board.chessboard[EndRowNo][EndColNo] = "WQ";
                board.chessboard[StartRowNo][StartColNo] = "--";
                return true;
            }
        }

        return false;
    }
};

int main() {
    ChessBoard board;
    BlackPieceMover blackMover(board);
    WhitePieceMover whiteMover(board);
    board.printChessBoard();
    int turn = 0;
    string moveInput;
    while (true) {
        getline(cin, moveInput);
        if (moveInput == "exit") {
            board.printChessBoard();
            break;
        }
        string startMove = moveInput.substr(0, 2);
        string endMove = moveInput.substr(3, 2);
        if (turn == 0) {
            if (whiteMover.Move(startMove, endMove)) {
                board.printChessBoard();
                turn = 1;
            } else {
                cout << "invalid" << endl;
            }
        } else {
            if (blackMover.Move(startMove, endMove)) {
                board.printChessBoard();
                turn = 0;
            } else {
                cout << "invalid" << endl;
            }
        }
    }
}
