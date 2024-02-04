#include "ai_import.h"
#include <algorithm>
#include <climits>
#include <cmath>
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
  void posibleMoves(string moves[]) {

    int arrPosition = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          string move = "";
          move += i;
          move += j;
          moves[arrPosition] = move;
        }
      }
    }
  }
  string Result(string action, char player) {
    string boardAsString = "";
    if (board[action[0]][action[1]] == '#') {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          boardAsString += board[i][j];
        }
      }
    }
    return boardAsString;
  }

  char **ExtractBoard(string action, char player) {
    string boardStr = Result(action, player);

    char **boardArr = new char *[3];

    for (int i = 0; i < 3; ++i) {
      boardArr[i] = new char[3];
    }
    int place = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        boardArr[i][j] = boardStr[place++];
      }
    }
    return boardArr;
  }

public:
  int MiniMax(string boardStr) {
    if (eval() != 100) { // non terminal state
      return eval();
    }

    int bestVal INT_MIN;
    int value;

    string moves[arrSize()];
    posibleMoves(moves);

    if (MaxingPlayerTurn()) {

      for (string move : moves) {
        value = MiniMax(Result(move, 'X'));
        bestVal = max(bestVal, value);
        // unfinished minimax alg finish tmrw
      }
      return bestVal;

    } else {
      bestVal = INT_MAX;

      for (string move : moves) {
        value = MiniMax(Result(move, 'O'));
        bestVal = min(bestVal, value);
      }
      return bestVal;
    }
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
  char board[3][3] = {{'#', '#', '#'}, {'#', '#', '#'}, {'#', '#', '#'}};
  string brd = "XX#O#####";
  minmaxAi minmax(board);
  cout << minmax.MiniMax(brd);
  return 0;
}
