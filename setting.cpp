#include <algorithm>
#include <bits/types/cookie_io_functions_t.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

using namespace std;

const std::string red("\033[0;31m");

vector<string> GetWinnigPatter(char board[3][3], char winner) {
  vector<string> Pattern;

  int indexOfRow;
  bool rowStreak = true;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == winner && rowStreak) {
        rowStreak = true;
        indexOfRow = i;
      } else {
        rowStreak = false;
        break;
      }
    }
    if (rowStreak) {
      break;
    }
  }

  int indexOfCol;
  bool colStreak = true;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[j][i] == winner && rowStreak) {
        colStreak = true;
        indexOfCol = i;
      } else {
        colStreak = false;
        break;
      }
    }
    if (colStreak) {
      break;
    }
  }

  if (rowStreak) {
    for (int i = 0; i < 3; i++) {
      string cordinates = to_string(indexOfRow);
      cordinates.append(to_string(i));
      Pattern.push_back(cordinates);
    }
  }
  if (colStreak) {
    for (int i = 0; i < 3; i++) {
      string cordinates = to_string(i);
      cordinates.append(to_string(indexOfCol));
      Pattern.push_back(cordinates);
    }
  }

  bool mainDiagonal = true;
  for (int i = 0; i < 3; ++i) {
    if (board[i][i] != winner) {
      mainDiagonal = false;
      break;
    }
  }

  bool antiDiagonal = true;
  for (int i = 0; i < 3; ++i) {
    if (board[i][2 - i] != winner) {
      antiDiagonal = false;
      break;
    }
  }
  if (mainDiagonal) {
    for (int i = 0; i < 3; i++) {
      string cordinates = to_string(i);
      cordinates.append(to_string(i));
      Pattern.push_back(cordinates);
    }
  }
  if (antiDiagonal) {
    for (int i = 0; i < 3; i++) {
      string cordinates = to_string(i);
      cordinates.append(to_string((2 - i)));
      Pattern.push_back(cordinates);
    }
  }

  return Pattern;
}

void PrintHiglitedWin(char board[3][3], vector<string> pattern) {
  string *ptrn = pattern.data();

  pair<int, int> coord;
  coord.first = stoi(ptrn[0]);
  coord.second = stoi(ptrn[1]);

  cout << coord.first << coord.second;

  int tmp = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < ptrn->length(); k++) {
        coord.first = stoi(ptrn[i]);
        coord.second = stoi(ptrn[i + 1]);
      }
      // finish comparing to check if should highlight
      cout << red << board[i][j];
    }
    cout << '\n';
  }
}

int main(int argc, char *argv[]) {
  char board[3][3] = {{'X', 'X', 'X'}, {'#', 'O', 'O'}, {'#', '#', '#'}};
  vector<string> coords = GetWinnigPatter(board, 'X');

  for (auto move : coords) {
    cout << move;
  }

  cout << '\n' << '\n';

  PrintHiglitedWin(board, coords);
  return 0;
}
