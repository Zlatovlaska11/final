#include "import.h"
#include <iostream>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

using namespace std;

const std::string red("\033[0;31m");
const std::string reset("\033[0m");

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

ArrayWithColors **PrintHiglitedWin(char board[3][3], vector<string> pattern) {
  string *ptrn = pattern.data();

  // ArrayWithColors **array = new ArrayWithColors *[3];

  // for (int i = 0; i < 3; ++i) {
  //   array[i] = new ArrayWithColors[3];
  // }

  ArrayWithColors **array;
  int tmp = 0;
  string hightliteCords = ptrn[0];

  bool color = false;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {

      for (int k = 0; k < 3; k++) {
        hightliteCords = ptrn[k];
        if (hightliteCords[0] - '0' == i && hightliteCords[1] - '0' == j) {
          color = true;
        }
      }
      array[i][j] = {(color) ? red : reset, board[i][j]};
      color = false;
    }
  }

  return array;
}

void deleteColoredCharArray(ArrayWithColors **array, int rows) {
  for (int i = 0; i < rows; ++i) {
    delete[] array[i];
  }
  delete[] array;
}

int getConsoleWidth() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  return size.ws_col;
}

void PrintHiglitedBoard(char board[3][3], char player) {

  int width = getConsoleWidth() / 2;

  vector<string> coords = GetWinnigPatter(board, player);

  ArrayWithColors **array = PrintHiglitedWin(board, coords);

  std::cout << string(width - 9, ' ') << "      1   2   3" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╔═══╦═══╦═══╗" << std::endl;
  std::cout << string(width - 9, ' ') << " A  ║ " << array[0][0].color
            << array[0][0].boardChar << reset << " ║ " << array[0][1].color
            << array[0][1].boardChar << reset << " ║ " << array[0][2].color
            << array[0][2].boardChar << reset << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╠═══╬═══╬═══╣" << std::endl;
  std::cout << string(width - 9, ' ') << " B  ║ " << array[1][0].color
            << array[1][0].boardChar << reset << " ║ " << array[1][1].color
            << array[1][1].boardChar << reset << " ║ " << array[1][2].color
            << array[1][2].boardChar << reset << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╠═══╬═══╬═══╣" << std::endl;
  std::cout << string(width - 9, ' ') << " C  ║ " << array[2][0].color
            << array[2][0].boardChar << reset << " ║ " << array[2][1].color
            << array[2][1].boardChar << reset << " ║ " << array[2][2].color
            << array[2][2].boardChar << reset << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╚═══╩═══╩═══╝" << std::endl;
}
