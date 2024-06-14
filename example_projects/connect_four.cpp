#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <stdexcept>

using namespace std;

enum GridPosition {
    EMPTY, YELLOW, RED
};

class Grid {
private:
    int rows;
    int columns;
    vector<vector<int>> grid;
    
public:
    Grid(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
        initGrid();
    }

    void initGrid() {
        this->grid = vector<vector<int>>();
        for (int i = 0; i < rows; i++) {
            this->grid.push_back(vector<int>());
            for (int j = 0; j < columns; j++) {
                grid[i].push_back(GridPosition::EMPTY);
            }
        }
    }

    vector<vector<int>> getGrid() {
        return this->grid;
    }

    int getColumnCount() {
        return this->columns;
    }

    int placePiece(int column, GridPosition piece) {
        if (column < 0 || column >= this->columns) {
            throw "Invalid column";
        }
        if (piece == GridPosition::EMPTY) {
            throw "Invalid piece";
        }
        // Place piece in the lowest empty row
        for (int row = this->rows - 1; row >= 0; row--) {
            if (this->grid[row][column] == GridPosition::EMPTY) {
                this->grid[row][column] = piece;
                return row;
            }
        }
        return -1;
    }

    bool checkWin(int connectN, int row, int col, GridPosition piece) {
        // Check horizontal
        int count = 0;
        for (int c = 0; c < this->columns; c++) {
            if (this->grid[row][c] == piece) {
                count++;
            } else {
                count = 0;
            }
            if (count == connectN) {
                return true;
            }
        }

        // Check vertical
        count = 0;
        for (int r = 0; r < this->rows; r++) {
            if (this->grid[r][col] == piece) {
                count++;
            } else {
                count = 0;
            }
            if (count == connectN) {
                return true;
            }
        }

        // Check diagonal
        count = 0;
        for (int r = 0; r < this->rows; r++) {
            int c = row + col - r; // row + col = r + c, for a diagonal
            if (c >= 0 && c < this->columns && this->grid[r][c] == piece) {
                count++;
            } else {
                count = 0;
            }
            if (count == connectN) {
                return true;
            }
        }

        // Check anti-diagonal
        count = 0;
        for (int r = 0; r < this->rows; r++) {
            int c = col - row + r; // row - col = r - c, for an anti-diagonal
            if (c >= 0 && c < this->columns && this->grid[r][c] == piece) {
                count++;
            } else {
                count = 0;
            }
            if (count == connectN) {
                return true;
            }
        }
        return false;
    }
};

class Player {
private:
    string name;
    GridPosition piece;

public:
    Player(string name, GridPosition piece) {
        this->name = name;
        this->piece = piece;
    }

    string getName() {
        return this->name;
    }

    GridPosition getPieceColor() {
        return this->piece;
    }
};

class Game {
private:
    Grid* grid;
    int connectN;
    vector<Player*> players;
    unordered_map<string, int> score;
    int targetScore;

public:
    Game(Grid* grid, int connectN, int targetScore) {
        this->grid = grid;
        this->connectN = connectN;
        this->targetScore = targetScore;

        this->players = vector<Player*> {
            new Player("Player 1", YELLOW),
            new Player("Player 2", RED)
        };

        this->score = unordered_map<string, int>();
        for (Player* player : this->players) {
            this->score[player->getName()] = 0;
        }
    }

    void printBoard() {
        cout << "Board:" << endl;
        vector<vector<int>> grid = this->grid->getGrid();
        for (int i = 0; i < grid.size(); i++) {
            string row = "";
            for (int piece : grid[i]) {
                if (piece == GridPosition::EMPTY) {
                    row += "0 ";
                } else if (piece == GridPosition::YELLOW) {
                    row += "Y ";
                } else if (piece == GridPosition::RED) {
                    row += "R ";
                }
            }
            cout << row << endl;
        }
        cout << endl;
    }

    vector<int> playMove(Player* player) {
        printBoard();
        cout << player->getName() << "'s turn" << endl;
        int colCnt = this->grid->getColumnCount();
        
        cout << "Enter column between 0 and " << (colCnt - 1) << " to add piece: ";
        int moveColumn = 0;
        cin >> moveColumn;
        
        int moveRow = this->grid->placePiece(moveColumn, player->getPieceColor());
        return vector<int> { moveRow, moveColumn };
    }

    Player* playRound() {
        while (true) {
            for (Player* player : this->players) {
                vector<int> pos = playMove(player);
                int row = pos[0];
                int col = pos[1];
                GridPosition pieceColor = player->getPieceColor();
                if (this->grid->checkWin(this->connectN, row, col, pieceColor)) {
                    this->score[player->getName()] = this->score[player->getName()] + 1;
                    return player;
                }
            }
        }
    }

    void play() {
        int maxScore = 0;
        Player* winner = nullptr;
        while (maxScore < this->targetScore) {
            winner = playRound();
            cout << winner->getName() << " won the round" << endl;
            maxScore = max(this->score[winner->getName()], maxScore);

            this->grid->initGrid(); // reset grid
        } 
        cout << winner->getName() << " won the game" << endl;
    }
};

int main() {
    Grid* grid = new Grid(6, 7);
    Game* game = new Game(grid, 4, 10);
    game->play();
    return 0;
}