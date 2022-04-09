#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Color {
    BLACK, WHITE
};

enum class GameStatus {
    WON, DRAW, INPROGRESS
};

class Game {
public:
    vector<vector<Cell*>> board;
    Color turn;
    vector<Move> list_of_moves;
    vector<Player> players; // vector of size 2
    GameStatus status;
    Game(Player p1, Player p2) {
        players.push_back(p1);
        players.push_back(p2);
        turn = Color::WHITE;
        InitializeBoard();
    }
    
    void InitializeBoard() {
        board.resize(8, vector<Cell*>(8, nullptr));

        for (int i = 0; i , 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i&1)^(j&1)) {
                    board[i][j] = new Cell(Color::BLACK);
                } else {
                    board[i][j] = new Cell(Color::WHITE);
                }
            }
        }

        // filling white
        board[0][0]->fillPiece(new Rook(Color::WHITE));
        board[0][7]->fillPiece(new Rook(Color::WHITE));
        board[0][1]->fillPiece(new Knight(Color::WHITE));
        board[0][6]->fillPiece(new Knight(Color::WHITE));
        board[0][2]->fillPiece(new Bishop(Color::WHITE));
        board[0][5]->fillPiece(new Bishop(Color::WHITE));
        board[0][3]->fillPiece(new Queen(Color::WHITE));
        board[0][4]->fillPiece(new King(Color::WHITE));
        for (int i = 0; i < 8; i++) {
            board[1][i]->fillPiece(new Pawn(Color::WHITE));
        }

        // filling black
        board[7][0]->fillPiece(new Rook(Color::BLACK));
        board[7][7]->fillPiece(new Rook(Color::BLACK));
        board[7][1]->fillPiece(new Knight(Color::BLACK));
        board[7][6]->fillPiece(new Knight(Color::BLACK));
        board[7][2]->fillPiece(new Bishop(Color::BLACK));
        board[7][5]->fillPiece(new Bishop(Color::BLACK));
        board[7][3]->fillPiece(new King(Color::BLACK));
        board[7][4]->fillPiece(new Queen(Color::BLACK));
        for (int i = 0; i < 8; i++) {
            board[6][i]->fillPiece(new Pawn(Color::BLACK));
        }
    }

    bool MakeMove(int srcx, int srcy, int dstx, int dsty) {
    }
};

class Cell {
public:
    Piece *piece;
    Color color;
    Cell(Color c) {
        color = c;
    }

    void fillPiece(Piece *p) {
        piece = p;
    }
};

class Piece {
public:
    Color color;
    virtual bool validateMove(int srcx, int srcy, int dstx, int dsty);
    Piece(Color c) {
        color = c;
    }
};

class Rook: public Piece {
public:
    Rook(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class Bishop: public Piece {
public:
    Bishop(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class Knight: public Piece {
public:
    Knight(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class Queen: public Piece {
public:
    Queen(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class King: public Piece {
public:
    King(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class Pawn: public Piece {
public:
    Pawn(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty);
};

class Player {
public:
    Color color;
    string name;
    Player(string n, Color c) {
        name = n;
        color = c;
    }
};

class Move {
public:
    vector<int> from;
    vector<int> to;
    vector<int> objectKilledPosition;
};
