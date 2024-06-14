#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <string>

enum Color { WHITE = 1, BLACK = 2 };

class Piece;

class Square {
public:
    Color color;
    Piece* piece;

    Square(Color color) : color(color), piece(nullptr) {}

    void set_piece(Piece* new_piece) {
        piece = new_piece;
    }

    Piece* get_piece() {
        return piece;
    }
};

class Piece {
public:
    virtual ~Piece() {}
    virtual bool is_valid_move(int start_row, int start_col, int end_row, int end_col, Square* board[][8]) const = 0;
    virtual std::string get_symbol() const = 0;

    Color color;

    Piece(Color color) : color(color) {}

    Color get_color() const { return color; }

    static bool is_within_grid(int end_row, int end_col) {
        return 0 <= end_row && end_row <= 7 && 0 <= end_col && end_col <= 7;
    }
};

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        if (!Piece::is_within_grid(endRow, endCol)) return false;

        int rowMovement = endRow - startRow;
        int colMovement = endCol - startCol;

        int direction = (get_color() == Color::WHITE) ? -1 : 1;

        if (colMovement != 0) return false;

        if (rowMovement == direction && board[endRow][endCol]->get_piece() == nullptr) {
            return true;
        }

        if (
            isFirstMove(startRow) &&
            rowMovement == (2 * direction) &&
            board[startRow + direction][startCol]->get_piece() == nullptr &&
            board[endRow][endCol]->get_piece() == nullptr
        ) {
            return true;
        }

        return false;
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "P" : "p";
    }

private:
    bool isFirstMove(int startRow) const {
        return (get_color() == Color::WHITE && startRow == 6) || (get_color() == Color::BLACK && startRow == 1);
    }
};

class Knight : public Piece {
public:
    Knight(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        if (!Piece::is_within_grid(endRow, endCol)) return false;

        int rowMovement = std::abs(endRow - startRow);
        int colMovement = std::abs(endCol - startCol);

        if (rowMovement == 2 && colMovement == 1 || rowMovement == 1 && colMovement == 2) {
            if (
                board[endRow][endCol]->get_piece() != nullptr &&
                board[endRow][endCol]->get_piece()->get_color() == get_color()
            ) {
                return false;
            }
            return true;
        }

        return false;
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "N" : "n";
    }
};

class MovementUtil {
public:
    static bool is_valid_straight_move(
        int startRow, int startCol, 
        int endRow, int endCol, 
        Color color,
        Square* board[][8]
    ) {
        if (!Piece::is_within_grid(endRow, endCol)) return false;

        int rowMovement = std::abs(endRow - startRow);
        int colMovement = std::abs(endCol - startCol);

        if ((rowMovement != 0 && colMovement != 0) ||
            (rowMovement == 0 && colMovement == 0)) {
            return false;
        } else {
            int rowIncrement = (endRow > startRow) ? 1 : -1;
            int colIncrement = (endCol > startCol) ? 1 : -1;

            if (rowMovement == 0) {
                int y = startCol + colIncrement;
                while (y != endCol) {
                    if (board[startRow][y]->get_piece() != nullptr) {
                        return false;
                    }
                    y += colIncrement;
                }
            } else {
                int x = startRow + rowIncrement;
                while (x != endRow) {
                    if (board[x][startCol]->get_piece() != nullptr) {
                        return false;
                    }
                    x += rowIncrement;
                }
            }

            if (board[endRow][endCol]->get_piece() != nullptr &&
                board[endRow][endCol]->get_piece()->get_color() == color) {
                return false;
            }

            return true;
        }
    }

    static bool is_valid_diagonal_move(
        int startRow, int startCol,
        int endRow, int endCol,
        Color color,
        Square* board[][8]
    ) {
        if (!Piece::is_within_grid(endRow, endCol)) return false;

        int rowMovement = std::abs(endRow - startRow);
        int colMovement = std::abs(endCol - startCol);

        if (rowMovement == 0 || colMovement == 0) return false;

        if (rowMovement == colMovement) {
            int rowIncrement = (endRow > startRow) ? 1 : -1;
            int colIncrement = (endCol > startCol) ? 1 : -1;

            int x = startRow + rowIncrement;
            int y = startCol + colIncrement;

            while (x != endRow && y != endCol) {
                if (board[x][y]->get_piece() != nullptr) {
                    return false;
                }
                x += rowIncrement;
                y += colIncrement;
            }

            if (board[endRow][endCol]->get_piece() != nullptr &&
                board[endRow][endCol]->get_piece()->get_color() == color) {
                return false;
            }

            return true;
        } else {
            return false;
        }
    }
};

class Rook : public Piece {
public:
    Rook(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        return MovementUtil::is_valid_straight_move(startRow, startCol, endRow, endCol, get_color(), board);
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "R" : "r";
    }
};

class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        return MovementUtil::is_valid_diagonal_move(startRow, startCol, endRow, endCol, get_color(), board);
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "B" : "b";
    }
};

class King : public Piece {
public:
    King(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        if (!is_within_grid(endRow, endCol)) return false;

        int rowMovement = abs(endRow - startRow);
        int colMovement = abs(endCol - startCol);

        if (rowMovement > 1 || colMovement > 1) {
          return false;
        }

        if (
          board[endRow][endCol]->get_piece() != nullptr &&
          board[endRow][endCol]->get_piece()->get_color() == get_color()
        ) {
          return false;
        }

        return true;
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "K" : "k";
    }
};

class Queen : public Piece {
public:
    Queen(Color color) : Piece(color) {}

    bool is_valid_move(int startRow, int startCol, int endRow, int endCol, Square* board[][8]) const override {
        return MovementUtil::is_valid_diagonal_move(startRow, startCol, endRow, endCol, get_color(), board) ||
            MovementUtil::is_valid_straight_move(startRow, startCol, endRow, endCol, get_color(), board);
    }

    std::string get_symbol() const override {
        return (get_color() == Color::WHITE) ? "Q" : "q";
    }
};

class Player {
private:
    Color color;

public:
    Player(Color color) : color(color) {}
    
    Color get_color() { return color; }
};

class ChessBoard {
private:
    Square* board[8][8];

public:
    ChessBoard() {
        initialize_board_and_pieces();
    }

    void initialize_board_and_pieces() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Color square_color = (i + j) % 2 == 0 ? Color::BLACK : Color::WHITE;
                board[i][j] = new Square(square_color);
            }
        }
        initialize_black_pieces();
        initialize_white_pieces();
    }

    void initialize_black_pieces() {
        for (int i = 0; i < 8; i++) {
            board[1][i]->set_piece(new Pawn(Color::BLACK));
        }
        board[0][0]->set_piece(new Rook(Color::BLACK));
        board[0][7]->set_piece(new Rook(Color::BLACK));
        board[0][1]->set_piece(new Knight (Color::BLACK));
        board[0][6]->set_piece(new Knight (Color::BLACK));
        board[0][2]->set_piece(new Bishop (Color::BLACK));
        board[0][5]->set_piece(new Bishop (Color::BLACK));
        board[0][3]->set_piece(new Queen (Color::BLACK));
        board[0][4]->set_piece(new King (Color::BLACK));
    }

    void initialize_white_pieces() {
        for (int i = 0; i < 8; i++) {
            board[6][i]->set_piece(new Pawn(Color::WHITE));
        }
        board[7][0]->set_piece(new Rook(Color::WHITE));
        board[7][7]->set_piece(new Rook(Color::WHITE));
        board[7][1]->set_piece(new Knight (Color::WHITE));
        board[7][6]->set_piece(new Knight (Color::WHITE));
        board[7][2]->set_piece(new Bishop (Color::WHITE));
        board[7][5]->set_piece(new Bishop (Color::WHITE));
        board[7][3]->set_piece(new Queen (Color::WHITE));
        board[7][4]->set_piece(new King (Color::WHITE));
    }


    bool move_piece(Player current_player) {
        int start_row, start_col, end_row, end_col;
        while (true) {
            std::cout << "Enter starting row: ";
            std::cin >> start_row;
            std::cout << "Enter starting column: ";
            std::cin >> start_col;
            std::cout << "Enter destination row: ";
            std::cin >> end_row;
            std::cout << "Enter destination column: ";
            std::cin >> end_col;

            if (!Piece::is_within_grid(end_row, end_col)) {
                return false;
            }

            Piece* piece_to_move = board[start_row][start_col]->get_piece();

            if (piece_to_move == nullptr) {
                std::cout << "There's no piece at the specified starting position." << std::endl;
                continue;
            }

            if (piece_to_move->get_color() != current_player.get_color()) {
                std::cout << "It's not your turn to move this piece." << std::endl;
                continue;
            }

            if (piece_to_move->is_valid_move(start_row, start_col, end_row, end_col, board)) {
                Piece* destination_piece = board[end_row][end_col]->get_piece();

                if (destination_piece != nullptr && destination_piece->get_color() != piece_to_move->get_color()) {
                    board[end_row][end_col]->set_piece(nullptr);
                }

                board[end_row][end_col]->set_piece(std::move(board[start_row][start_col]->get_piece()));
                board[start_row][start_col]->set_piece(nullptr); // Clear the original square

                std::cout << piece_to_move->get_symbol() << " moved to " << end_row << ", " << end_col << std::endl;

                return true;
            } else {
                std::cout << "Invalid move for the " << piece_to_move->get_symbol() << ". Please try again." << std::endl;
            }
        }
    }

    void display_board() {
        std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
        std::cout << "  ---------------" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << i << "|";
            for (int j = 0; j < 8; j++) {
                if (board[i][j]->get_piece() != nullptr) {
                    std::cout << board[i][j]->get_piece()->get_symbol() << " ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }
};

class ChessGame {
private:
    ChessBoard board;
    Player white_player;
    Player black_player;

public:
    ChessGame() : white_player(Color::WHITE), black_player(Color::BLACK) {}

    void start_game() {
        std::cout << "Welcome to Chess, UPPERCASE denotes white, LOWERCASE denotes black" << std::endl;
        board.display_board();

        Player current_player = white_player;

        while (true) {
            std::cout << "Current turn: " << (current_player.get_color() == Color::WHITE ? "White" : "Black") << std::endl;

            bool moveSuccessful = board.move_piece(current_player);
            if (moveSuccessful) {
                board.display_board();
                current_player =
                    (current_player.get_color() == white_player.get_color()) ? black_player : white_player;
            } else {
                std::cout << "Invalid move, try again." << std::endl;
            }
        }
    }
};

int main() {
    ChessGame game;
    game.start_game();
    return 0;
}
