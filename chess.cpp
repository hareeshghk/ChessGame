#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

enum class Color {
    BLACK, WHITE
};

enum class GameStatus {
    WHITE_WIN, BLACK_WIN, DRAW, FORFEIGHT, ACTIVE
};
class Player {
public:
    Color color;
    string name;
    Player(string n, Color c) {
        name = n;
        color = c;
    }

    bool isWhite() {
        return color == Color::WHITE;
    }
};

class Piece {
public:
    Color color;
    virtual bool validateMove(int srcx, int srcy, int dstx, int dsty) = 0;
    virtual void PrintPiece() = 0;
    Piece(Color c) {
        color = c;
    }

    bool isWhite() {
        return color == Color::WHITE;
    }
};
class Cell {
public:
    shared_ptr<Piece> piece;
    Color color;
    int x, y;
    Cell(Color c, int x, int y) {
        color = c;
        piece = nullptr;
        this->x = x;
        this->y = y;
    }

    void fillPiece(shared_ptr<Piece> p) {
        piece = p;
    }

    void PrintCell() {
        if (piece == nullptr) {
            cout << " n ";
        } else {
            piece->PrintPiece();
        }
    }

    shared_ptr<Piece> GetPiece() {
        return piece;
    }
};

class Rook: public Piece {
public:
    Rook(Color c) : Piece(c) {
        color = Color::BLACK;
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " R ";
    }
};

class Bishop: public Piece {
public:
    Bishop(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " B ";
    }
};

class Knight: public Piece {
public:
    Knight(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " K ";
    }
};

class Queen: public Piece {
public:
    Queen(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " Q ";
    }
};

class King: public Piece {
public:
    King(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " K ";
    }
};

class Pawn: public Piece {
public:
    Pawn(Color c) : Piece(c) {
    }
    bool validateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }
    void PrintPiece() {
        cout << " P ";
    }
};

class Move {
public:
    shared_ptr<Cell> source;
    shared_ptr<Cell> destination;
    shared_ptr<Player> player;
    shared_ptr<Piece> movedPiece;
    shared_ptr<Piece> killedPiece;
};
class Game {
public:
    vector<vector<shared_ptr<Cell>>> board;
    shared_ptr<Player> currentPlayer;
    vector<Move> list_of_moves;
    vector<shared_ptr<Player>> players; // vector of size 2
    GameStatus status;
    Game(shared_ptr<Player> p1, shared_ptr<Player> p2) {
        players.push_back(p1);
        players.push_back(p2);
        if (players[0]->isWhite()) {
            currentPlayer = players[0];
        } else {
            currentPlayer = players[1];
        }
        InitializeBoard();
    }
    
    void InitializeBoard() {
        board.resize(8, vector<shared_ptr<Cell>>(8, nullptr));

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i&1)^(j&1)) {
                    board[i][j] = make_shared<Cell>(Color::BLACK,i,j);
                } else {
                    board[i][j] = make_shared<Cell>(Color::WHITE,i,j);
                }
            }
        }

        // filling white
        board[0][0]->fillPiece(make_shared<Rook>(Color::WHITE));
        board[0][7]->fillPiece(make_shared<Rook>(Color::WHITE));
        board[0][1]->fillPiece(make_shared<Knight>(Color::WHITE));
        board[0][6]->fillPiece(make_shared<Knight>(Color::WHITE));
        board[0][2]->fillPiece(make_shared<Bishop>(Color::WHITE));
        board[0][5]->fillPiece(make_shared<Bishop>(Color::WHITE));
        board[0][3]->fillPiece(make_shared<Queen>(Color::WHITE));
        board[0][4]->fillPiece(make_shared<King>(Color::WHITE));
        for (int i = 0; i < 8; i++) {
            board[1][i]->fillPiece(make_shared<Pawn>(Color::WHITE));
        }

        // filling black
        board[7][0]->fillPiece(make_shared<Rook>(Color::BLACK));
        board[7][7]->fillPiece(make_shared<Rook>(Color::BLACK));
        board[7][1]->fillPiece(make_shared<Knight>(Color::BLACK));
        board[7][6]->fillPiece(make_shared<Knight>(Color::BLACK));
        board[7][2]->fillPiece(make_shared<Bishop>(Color::BLACK));
        board[7][5]->fillPiece(make_shared<Bishop>(Color::BLACK));
        board[7][3]->fillPiece(make_shared<King>(Color::BLACK));
        board[7][4]->fillPiece(make_shared<Queen>(Color::BLACK));
        for (int i = 0; i < 8; i++) {
            board[6][i]->fillPiece(make_shared<Pawn>(Color::BLACK));
        }
    }

    bool MakeMove(shared_ptr<Player> player, int srcx, int srcy, int dstx, int dsty) {
        // validate vals with boundaries
        // validate if its current player turn
        // validate if src cell contains a peice
        // validate if piece belongs to current player
        // valide if peice in src can move to dst location by contacting its overloaded function
        // validate no pice present in path for non knight cases
        // create Move object and fill it, include if any peice is dead
        auto srcCell = board[srcx][srcy];
        auto dstCell = board[dstx][dsty];

        if (srcCell->GetPiece() == nullptr) return false;

        board[dstx][dsty]->fillPiece(srcCell->GetPiece());
        board[srcx][srcy]->fillPiece(nullptr);

        // if (!ValidateMove(srcx, srcy, dstx, dsty)) return false;
        changeTurn();
        return true;
    }

    void changeTurn() {
        if (currentPlayer == players[0]) {
            currentPlayer = players[1];
        } else {
            currentPlayer = players[0];
        }
    }

    bool ValidateMove(int srcx, int srcy, int dstx, int dsty) {
        return true;
    }

    void PrintBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j]->PrintCell();
            }
            cout << endl;
        }
    }

    shared_ptr<Player> getCurrentPlayer() {
        return currentPlayer;
    }
};

int main() {
    shared_ptr<Player> p1 = make_shared<Player>("Hareesh", Color::WHITE);
    shared_ptr<Player> p2 = make_shared<Player>("Kumar", Color::BLACK);

    Game game(p1, p2);

    int srcx, srcy, endx, endy;
    while (true) {
        game.PrintBoard();
        cout << "Choose Starting and Ending Positions: ";
        cin >> srcx >> srcy >> endx >> endy;

        if(!game.MakeMove(game.getCurrentPlayer(), srcx, srcy, endx, endy)) {
            continue;
        }
        // break;
    }
    return 0;
}
