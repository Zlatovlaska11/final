#include <algorithm>
#include <climits>
#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;

class minmaxAi {
private:
  char board[3][3];
  char boardAfterAction[3][3];

  bool isTerminalState(char player) {
    for (int i = 0; i < 3; ++i) {
      if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
           board[i][0] == player) ||
          (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
           board[0][i] == player)) {
        return true;
      }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
         board[0][0] == player) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
         board[0][2] == player)) {
      return true;
    }
    return false;
  }
  bool IsBoardFull() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          return false;
        }
      }
    }
    return true;
  }

  int eval() {
    if (isTerminalState('X')) {
      return 1;
    } else if (isTerminalState('O')) {
      return -1;
    } else if (IsBoardFull()) {
      return 0;
    } else {
      return 100;
    }
  }

  bool MaxingPlayerTurn() {
    int x = 0;
    int o = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == 'X') {
          x++;
        } else if (board[i][j] == 'O') {
          o++;
        }
      }
    }
    return x == o;
  }

  // void posibleMoves() {
  //   int count = 0;
  //   int sqare = 0;
  //   for (int i = 0; i < 3; i++) {
  //     for (int j = 0; j < 3; j++) {
  //       sqare++;
  //     }
  //   }
  //   for (int i = 0; i < 3; i++) {
  //     for (int j = 0; j < 3; j++) {
  //       sqare++;
  //       if (board[i][j] == '#') {
  //         moves = sqare;

  //     }
  //}
  //}
  //}
  int arrSize() {
    int arrSize = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          arrSize++;
        }
      }
    }
    return arrSize;
  }
  vector<string> posibleMoves() {
    int arrPosition = 0;
    vector<string> moves;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          string move = to_string(i) + to_string(j);
          moves.push_back(move);
        }
      }
    }
    return moves;
  }

  string Result(string action, char player) {

    string boardAsString = "";

    // Create a temporary copy of the board
    char tempBoard[3][3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        tempBoard[i][j] = board[i][j];
      }
    }

    int row = action[0] - '0';
    int col = action[1] - '0';

    if (tempBoard[row][col] == '#') {
      // Update the temporary board
      tempBoard[row][col] = player;

      // Convert the updated temporary board to a string
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          boardAsString += tempBoard[i][j];
        }
      }
    }
    return boardAsString;
  }

public:
  int MiniMax(string boardStr) {
    if (eval() != 100) { // non terminal state
      return eval();
    }

    int bestVal INT_MIN;
    int value;

    vector<string> tmpMoves = posibleMoves();

    // string parsing error

    if (MaxingPlayerTurn()) {

      for (string move : tmpMoves) {
        value = MiniMax(Result(move, 'X'));
        bestVal = max(bestVal, value);
        // unfinished minimax alg finish tmrw
      }
      return bestVal;

    } else {
      bestVal = INT_MAX;

      for (string move : tmpMoves) {
        value = MiniMax(Result(move, 'O'));
        bestVal = min(bestVal, value);
      }
      return bestVal;
    }
  }

  int evaluate_board(const string &current_board) {
    return MiniMax(current_board);
  }

  minmaxAi(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        this->board[i][j] = board[i][j];
      }
    }
  }
};

int main(int argc, char *argv[]) {
  char board[3][3] = {{'X', 'X', '#'}, {'O', 'O', '#'}, {'#', '#', '#'}};
  string brd = "XX#OO####";
  minmaxAi minmax(board);
  std::cout << minmax.evaluate_board(brd);
  return 0;
}
