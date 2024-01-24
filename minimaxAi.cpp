#include <climits>
#include <iostream>

using namespace std;

const int BOARD_SIZE = 3;

bool is_winner(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  // Check rows, columns, and diagonals for a win
  for (int i = 0; i < BOARD_SIZE; ++i) {
    if ((board[i][0] == player && board[i][1] == player &&
         board[i][2] == player) ||
        (board[0][i] == player && board[1][i] == player &&
         board[2][i] == player)) {
      return true;
    }
  }

  if ((board[0][0] == player && board[1][1] == player &&
       board[2][2] == player) ||
      (board[0][2] == player && board[1][1] == player &&
       board[2][0] == player)) {
    return true;
  }

  return false;
}

bool is_board_full(char board[BOARD_SIZE][BOARD_SIZE]) {
  // Check if the board is full
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

int evaluate(char board[BOARD_SIZE][BOARD_SIZE]) {
  // Evaluate the current state of the board
  if (is_winner(board, 'X')) {
    return 1;
  } else if (is_winner(board, 'O')) {
    return -1;
  } else if (is_board_full(board)) {
    return 0;
  } else {
    return INT_MAX; // Placeholder for non-terminal state
  }
}

int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth,
            bool maximizing_player) {
  int score = evaluate(board);

  if (score != INT_MAX) {
    return score;
  }

  if (maximizing_player) {
    int max_eval = INT_MIN;
    for (int i = 0; i < BOARD_SIZE; ++i) {
      for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[i][j] == ' ') {
          board[i][j] = 'X';
          int eval = minimax(board, depth + 1, false);
          board[i][j] = ' ';
          max_eval = max(max_eval, eval);
        }
      }
    }
    return max_eval;
  } else {
    int min_eval = INT_MAX;
    for (int i = 0; i < BOARD_SIZE; ++i) {
      for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[i][j] == ' ') {
          board[i][j] = 'O';
          int eval = minimax(board, depth + 1, true);
          board[i][j] = ' ';
          min_eval = min(min_eval, eval);
        }
      }
    }
    return min_eval;
  }
}

pair<int, int> get_best_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  int best_val = INT_MIN;
  pair<int, int> best_move = {-1, -1};

  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (board[i][j] == ' ') {
        board[i][j] = 'X';
        int move_val = minimax(board, 0, false);
        board[i][j] = ' ';

        if (move_val > best_val) {
          best_move = {i, j};
          best_val = move_val;
        }
      }
    }
  }

  return best_move;
}

int main() {
  char board[BOARD_SIZE][BOARD_SIZE] = {
      {'X', 'O', ' '}, {' ', 'X', 'O'}, {'O', ' ', 'X'}};

  pair<int, int> best_move = get_best_move(board);
  cout << "Best move: (" << best_move.first << ", " << best_move.second
       << ")\n";

  return 0;

  // finish inmplemntingthe int to string function unsing switch and returning
  // it to be used in the game.cpp
}
