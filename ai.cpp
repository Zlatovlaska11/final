#include "ai_import.h"
#include <algorithm>
#include <cstddef>
#include <curses.h>
#include <list>
#include <string>
#include <unistd.h>
#include <utility>
using namespace std;

class minmaxAi {
private:
  char board[3][3];
  char boardAfterAction[3][3];

  list<string> moves;

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
  void posibleMoves() {
    int arrSize = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          arrSize++;
        }
      }
    }
    int arrPosition = 0;
    int sqare = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        sqare++;
        if (board[i][j] == '#') {
          string move = "";
          move += i;
          move += j;
          moves.push_back(move);
        }
      }
    }
  }
  void Result(string action, char player) {
    if (board[action[0]][action[1]] == '#') {
      boardAfterAction[action[0]][action[1]] = player;
    } else {
      throw "TF";
    }
  }

public:
  int MiniMax() {
    if (eval() != 100) { // non terminal state
      return eval();
    }
    return 0;
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
  char board[3][3] = {{'O', 'O', 'O'}, {'X', 'X', '#'}, {'#', '#', '#'}};
  minmaxAi minmax(board);
  cout << minmax.MiniMax();
  return 0;
}
