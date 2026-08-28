#include <iostream>
#include <array>
#include <limits>
#include <string>

using namespace std;

class TicTacToe {
private:
    array<char, 9> board;
    char currentPlayer;
    int playerXWins;
    int playerOWins;
    int draws;

    void resetBoard() {
        for (int i = 0; i < 9; i++) {
            board[i] = static_cast<char>('1' + i);
        }

        currentPlayer = 'X';
    }

    void showBoard() const {
        cout << "\n";
        cout << "        TIC TAC TOE\n";
        cout << "      ----------------\n\n";

        cout << "          " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
        cout << "         ---+---+---\n";
        cout << "          " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
        cout << "         ---+---+---\n";
        cout << "          " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
    }

    bool isPositionAvailable(int position) const {
        int index = position - 1;

        return board[index] != 'X' && board[index] != 'O';
    }

    int getPlayerMove() {
        int position;

        while (true) {
            cout << "Player " << currentPlayer
                 << ", choose a position (1-9): ";

            cin >> position;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid input. Please enter a number from 1 to 9.\n";
                continue;
            }

            if (position < 1 || position > 9) {
                cout << "Position must be between 1 and 9.\n";
                continue;
            }

            if (!isPositionAvailable(position)) {
                cout << "That position is already occupied. Try another one.\n";
                continue;
            }

            return position;
        }
    }

    bool hasWon(char player) const {
        const int winningPatterns[8][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},

            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},

            {0, 4, 8},
            {2, 4, 6}
        };

        for (int i = 0; i < 8; i++) {
            int first = winningPatterns[i][0];
            int second = winningPatterns[i][1];
            int third = winningPatterns[i][2];

            if (board[first] == player &&
                board[second] == player &&
                board[third] == player) {
                return true;
            }
        }

        return false;
    }

    bool isBoardFull() const {
        for (char cell : board) {
            if (cell != 'X' && cell != 'O') {
                return false;
            }
        }

        return true;
    }

    void changePlayer() {
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        } else {
            currentPlayer = 'X';
        }
    }

    void showScoreboard() const {
        cout << "\n";
        cout << "          SCOREBOARD\n";
        cout << "      ------------------\n";
        cout << "      Player X Wins : " << playerXWins << "\n";
        cout << "      Player O Wins : " << playerOWins << "\n";
        cout << "      Draws         : " << draws << "\n";
        cout << "      ------------------\n";
    }

    bool askForReplay() const {
        char choice;

        while (true) {
            cout << "\nPlay another round? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                return true;
            }

            if (choice == 'N' || choice == 'n') {
                return false;
            }

            cout << "Please enter Y or N.\n";
        }
    }

    void playSingleRound() {
        resetBoard();

        while (true) {
            showBoard();

            int position = getPlayerMove();

            board[position - 1] = currentPlayer;

            if (hasWon(currentPlayer)) {
                showBoard();

                cout << "Player " << currentPlayer
                     << " wins this round!\n";

                if (currentPlayer == 'X') {
                    playerXWins++;
                } else {
                    playerOWins++;
                }

                break;
            }

            if (isBoardFull()) {
                showBoard();

                cout << "The round ended in a draw.\n";
                draws++;

                break;
            }

            changePlayer();
        }

        showScoreboard();
    }

public:
    TicTacToe()
        : currentPlayer('X'),
          playerXWins(0),
          playerOWins(0),
          draws(0) {
        resetBoard();
    }

    void start() {
        cout << "====================================\n";
        cout << "        MINI GAME PROJECT\n";
        cout << "           TIC TAC TOE\n";
        cout << "====================================\n";

        cout << "\nRules:\n";
        cout << "1. Player X starts the game.\n";
        cout << "2. Players choose positions from 1 to 9.\n";
        cout << "3. Get three marks in a row to win.\n";
        cout << "4. A filled board without a winner is a draw.\n";

        bool keepPlaying = true;

        while (keepPlaying) {
            playSingleRound();
            keepPlaying = askForReplay();
        }

        cout << "\n====================================\n";
        cout << "           FINAL SCORE\n";
        cout << "====================================\n";

        showScoreboard();

        cout << "\nThanks for playing Tic Tac Toe!\n";
    }
};

int main() {
    TicTacToe game;
    game.start();

    return 0;
}