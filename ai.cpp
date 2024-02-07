#include "ai_import.h"
#include <algorithm>
#include <climits>
#include <curses.h>
#include <unistd.h>
#include <utility>
using namespace std;

class minmaxAi {
private:
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

    bool mainDiagonal = true;
    for (int i = 0; i < 3; ++i) {
      if (board[i][i] != player) {
        mainDiagonal = false;
        break;
      }
    }

    bool antiDiagonal = true;
    for (int i = 0; i < 3; ++i) {
      if (board[i][2 - i] != player) {
        antiDiagonal = false;
        break;
      }
    }

    return mainDiagonal || antiDiagonal;
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

    if (evaluation != 100) { // non terminal state
      return evaluation;
    }

    if (MaxingPlayer) {
      int bestVal = INT_MIN;
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (boardCurrent[i][j] == '#') {
            boardCurrent[i][j] = 'X';
            int value = MiniMax(boardCurrent, false);
            boardCurrent[i][j] = '#';
            bestVal = std::max(bestVal, value);
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
            int value = MiniMax(boardCurrent, true);
            boardCurrent[i][j] = '#';
            minVal = std::min(minVal, value);
          }
        }
      }
      return minVal;
    }
  }
  pair<int, int> GetBestMove(char board[3][3], bool maxingPlayer, char player) {
    pair<int, int> BestMoves;

    int BestEval = (player == 'X') ? INT_MIN : INT_MAX;
    int eval;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '#') {
          board[i][j] = player;
          int eval = MiniMax(board, maxingPlayer);
          board[i][j] = '#';
          if ((player == 'X' && BestEval < eval) ||
              (player == 'O' && eval < BestEval)) {
            BestEval = eval;
            BestMoves.first = i;
            BestMoves.second = j;
          }
        }
      }
    }

    return BestMoves;
  }

  int evaluate_board(char boardCurrent[3][3], bool maxPlayr) {
    return MiniMax(boardCurrent, maxPlayr);
  }
};

pair<int, int> GetBestMove(char board[3][3], bool MaxingPlayerTurn,
                           char player) {
  minmaxAi ai;
  pair<int, int> bestMove = ai.GetBestMove(board, MaxingPlayerTurn, player);
  sleep(1);
  return bestMove;
}
