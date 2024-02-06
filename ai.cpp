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

  pair<int, int> ConvertMove(char move) {
    pair<int, int> moves;
    switch (move) {
    case '1':
      moves.first = 0;
      moves.second = 0;
      break;
    case '2':
      moves.first = 0;
      moves.second = 1;
      break;
    case '3':
      moves.first = 0;
      moves.second = 2;
      break;
    case '4':
      moves.first = 1;
      moves.second = 0;
      break;
    case '5':
      moves.first = 1;
      moves.second = 1;
      break;
    case '6':
      moves.first = 1;
      moves.second = 2;
      break;
    case '7':
      moves.first = 2;
      moves.second = 0;
      break;
    case '8':
      moves.first = 2;
      moves.second = 1;
      break;
    case '9':
      moves.first = 2;
      moves.second = 2;
      break;
    }
    return moves;
  }

public:
  int MiniMax(char boardCurrent[3][3], bool MaxingPlayer) {
    if (eval() != 100) { // non terminal state
      return eval();
    }

    int bestVal INT_MIN;
    int value;

    // string parsing error

    if (MaxingPlayer) {

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (boardCurrent[i][j] == '#') {
            boardCurrent[i][j] = 'X';
            value = MiniMax(boardCurrent, false);
            boardCurrent[i][j] = '#';
            bestVal = max(bestVal, value);
          }
        }
        // unfinished minimax alg finish tmrw
      }

      return bestVal;
    } else {
      int minVal = INT_MAX;

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (boardCurrent[i][j] == '#') {
            boardCurrent[i][j] = 'O';
            value = MiniMax(boardCurrent, true);
            boardCurrent[i][j] = '#';
            bestVal = min(bestVal, value);
          }
        }
        // unfinished minimax alg finish tmrw
      }

      return minVal;
    }
  }

  int evaluate_board(char boardCurrent[3][3], bool maxPlayr) {
    return MiniMax(boardCurrent, maxPlayr);
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
  std::cout << minmax.evaluate_board(board, true);
  return 0;
}
