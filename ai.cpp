#include <algorithm>
#include <climits>
#include <curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>
using namespace std;

class minmaxAi {
private:
  // char board[3][3];
  char boardAfterAction[3][3];

  bool isTerminalState(char player, char board[3][3]) {
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
  bool IsBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          return false;
        }
      }
    }
    return true;
  }

  int eval(char board[3][3]) {
    if (isTerminalState('X', board)) {
      return 1;
    } else if (isTerminalState('O', board)) {
      return -1;
    } else if (IsBoardFull(board)) {
      return 0;
    } else {
      return 100;
    }
  }

  bool MaxingPlayerTurn(char board[3][3]) {
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

public:
  int MiniMax(char boardCurrent[3][3], bool MaxingPlayer) {

    int evaluation = eval(boardCurrent);

    // cout << evaluation << endl;

    if (eval(boardCurrent) != 100) { // non terminal state
      return eval(boardCurrent);
    }

    int bestVal = INT_MIN;
    int value;

    // string parsing error

    if (MaxingPlayer) {

      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (boardCurrent[i][j] == '#') {
            boardCurrent[i][j] = 'X';
            value = MiniMax(boardCurrent, false);
            boardCurrent[i][j] = '#';
            bestVal = max(bestVal, value);
          }
        }
      }
      return bestVal;
    } else {
      int minVal = INT_MAX;

      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (boardCurrent[i][j] == '#') {
            boardCurrent[i][j] = 'O';
            value = MiniMax(boardCurrent, true);
            boardCurrent[i][j] = '#';
            minVal = min(minVal, value);
          }
        }
        // unfinished minimax alg finish tmrw
      }
      return minVal;
    }
  }
  pair<int, int> GetBestMove(char board[3][3], bool maxingPlayer) {
    pair<int, int> BestMoves;

    return BestMoves;
  }

  int evaluate_board(char boardCurrent[3][3], bool maxPlayr) {
    return MiniMax(boardCurrent, maxPlayr);
  }
};

int main(int argc, char *argv[]) {
  char board[3][3] = {{'X', 'X', '#'}, {'O', 'O', '#'}, {'X', '#', '#'}};
  minmaxAi minmax;
  std::cout << minmax.evaluate_board(board, false);
  return 0;
}
