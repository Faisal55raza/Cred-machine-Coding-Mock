#include <bits/stdc++.h>
using namespace std;

const int BOARD_SIZE = 8;

class Pieces {
protected:
    string color;

public:
    Pieces(string color) : color(color) {}
    virtual bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) = 0;
    virtual string pieceName() = 0;
    string getColor() {
        return color;
    }
};

class Pawn : public Pieces {
public:
    Pawn(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'P';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        int direction = (color == "White") ? -1 : 1;
        int initialRow = (color == "White") ? 6 : 1;

        if (startCol == targetCol) {
            if (startRow + direction == targetRow)
                return true;
            if (startRow == initialRow && startRow + 2 * direction == targetRow)
                return true;
        } else if (abs(startCol - targetCol) == 1 && startRow + direction == targetRow) {
            return true;  // Capture move
        }

        return false;
    }
};

class Rook : public Pieces {
public:
    Rook(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'R';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        return startCol == targetCol || startRow == targetRow;
    }
};

class Knight : public Pieces {
public:
    Knight(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'N';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        return (abs(startCol - targetCol) == 2 && abs(startRow - targetRow) == 1) ||
               (abs(startCol - targetCol) == 1 && abs(startRow - targetRow) == 2);
    }
};

class Bishop : public Pieces {
public:
    Bishop(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'B';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        return abs(startCol - targetCol) == abs(startRow - targetRow);
    }
};

class Queen : public Pieces {
public:
    Queen(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'Q';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        return abs(startCol - targetCol) == abs(startRow - targetRow) || startCol == targetCol || startRow == targetRow;
    }
};

class King : public Pieces {
public:
    King(string color) : Pieces(color) {}

    string pieceName() override {
        return string(1, color[0]) + 'K';
    }

    bool isValidMove(int startCol, int startRow, int targetCol, int targetRow) override {
        return abs(startCol - targetCol) <= 1 && abs(startRow - targetRow) <= 1;
    }
};

class ChessBoard {
protected:
    vector<vector<Pieces*>> chessPlayingBoard;

public:
    ChessBoard() {
        chessPlayingBoard.resize(BOARD_SIZE, vector<Pieces*>(BOARD_SIZE, nullptr));

        // Placing Black Pieces
        chessPlayingBoard[0][0] = new Rook("Black");
        chessPlayingBoard[0][7] = new Rook("Black");
        chessPlayingBoard[0][1] = new Knight("Black");
        chessPlayingBoard[0][6] = new Knight("Black");
        chessPlayingBoard[0][2] = new Bishop("Black");
        chessPlayingBoard[0][5] = new Bishop("Black");
        chessPlayingBoard[0][3] = new Queen("Black");
        chessPlayingBoard[0][4] = new King("Black");
        for (int i = 0; i < 8; ++i) {
            chessPlayingBoard[1][i] = new Pawn("Black");
        }

        // Placing White Pieces
        chessPlayingBoard[7][0] = new Rook("White");
        chessPlayingBoard[7][7] = new Rook("White");
        chessPlayingBoard[7][1] = new Knight("White");
        chessPlayingBoard[7][6] = new Knight("White");
        chessPlayingBoard[7][2] = new Bishop("White");
        chessPlayingBoard[7][5] = new Bishop("White");
        chessPlayingBoard[7][3] = new Queen("White");
        chessPlayingBoard[7][4] = new King("White");
        for (int i = 0; i < 8; ++i) {
            chessPlayingBoard[6][i] = new Pawn("White");
        }
    }

    ~ChessBoard() {
        for (auto &row : chessPlayingBoard) {
            for (auto &piece : row) {
                delete piece;
            }
        }
    }

    void print_ChessBoard() {
        for (const auto& row : chessPlayingBoard) {
            for (const auto& cell : row) {
                if (cell)
                    cout << cell->pieceName() << " ";
                else
                    cout << "-- ";
            }
            cout << endl;
        }
    }

    vector<vector<Pieces*>>& getBoard() {
        return chessPlayingBoard;
    }
};

class ChessManager {
protected:
    ChessBoard& chessPlayingBoard;

public:
    ChessManager(ChessBoard& chessPlayingBoard) : chessPlayingBoard(chessPlayingBoard) {}

    bool ValidateBoard(string PlayerColor, int startColPosition, int startRowPosition, int targetRowPosition, int targetColPosition) {
        if (startColPosition >= BOARD_SIZE || startRowPosition >= BOARD_SIZE ||
            targetColPosition >= BOARD_SIZE || targetRowPosition >= BOARD_SIZE ||
            startColPosition < 0 || startRowPosition < 0 || targetColPosition < 0 || targetRowPosition < 0)
            return false;

        Pieces* startPiece = chessPlayingBoard.getBoard()[startRowPosition][startColPosition];
        if (startPiece == nullptr || startPiece->getColor() != PlayerColor)
            return false;

        return true;
    }

    bool movePiece(string PlayerColor, string startPos, string targetPos) {
        int startColPosition = startPos[0] - 'a';
        int startRowPosition = 8 - (startPos[1] - '0');
        int targetColPosition = targetPos[0] - 'a';
        int targetRowPosition = 8 - (targetPos[1] - '0');

        if (!ValidateBoard(PlayerColor, startColPosition, startRowPosition, targetRowPosition, targetColPosition))
            return false;

        Pieces* SourcePiece = chessPlayingBoard.getBoard()[startRowPosition][startColPosition];

        if (SourcePiece->isValidMove(startColPosition, startRowPosition, targetColPosition, targetRowPosition)) {
            Pieces* targetPiece = chessPlayingBoard.getBoard()[targetRowPosition][targetColPosition];

            if (SourcePiece->pieceName()[1] == 'P' && targetPiece == nullptr && startColPosition != targetColPosition) 
                return false; 
            
            chessPlayingBoard.getBoard()[targetRowPosition][targetColPosition] = SourcePiece;
            chessPlayingBoard.getBoard()[startRowPosition][startColPosition] = nullptr;

            return true;
        }

        return false;
    }

    void printBoard() {
        chessPlayingBoard.print_ChessBoard();
    }
};

void ExecuteGame() {
    ChessBoard chessBoard1;
    ChessManager chessManager1(chessBoard1);
    chessManager1.printBoard();

    vector<string> Player{"White", "Black"};
    int turn = 0;
    string moveInput;

    while (true) {
        cout << Player[turn] << "'s turn. Enter move (e.g., e2 e4): ";
        getline(cin, moveInput);
        if (moveInput == "exit") {
            break;
        }
        string startMove = moveInput.substr(0, 2);
        string endMove = moveInput.substr(3, 2);

        if (chessManager1.movePiece(Player[turn], startMove, endMove)) {
            chessManager1.printBoard();
            turn = 1 - turn;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

int main() {
    ExecuteGame();
    return 0;
}
