#include <cstring>
#include <ios>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

using namespace std;

void DisplayBoard(char board[3][3]);

int main(int argc, char *argv[]) {
  char board[3][3] = {{'#', '#', 'X'}, {'#', 'O', '#'}, {'X', 'O', 'X'}};
  DisplayBoard(board);
}
int getConsoleWidth() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  return size.ws_col;
}

void DisplayBoard(char board[3][3]) {
  int width = getConsoleWidth() / 2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == '#') {
        board[i][j] = ' ';
      }
    }
  }

  std::cout << string(width - 9, ' ') << "      1   2   3" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╔═══╦═══╦═══╗" << std::endl;
  std::cout << string(width - 9, ' ') << " A  ║ " << board[0][0] << " ║ "
            << board[0][1] << " ║ " << board[0][2] << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╠═══╬═══╬═══╣" << std::endl;
  std::cout << string(width - 9, ' ') << " B  ║ " << board[1][0] << " ║ "
            << board[1][1] << " ║ " << board[1][2] << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╠═══╬═══╬═══╣" << std::endl;
  std::cout << string(width - 9, ' ') << " C  ║ " << board[2][0] << " ║ "
            << board[2][1] << " ║ " << board[2][2] << " ║" << std::endl;
  std::cout << string(width - 9, ' ') << "    ╚═══╩═══╩═══╝" << std::endl;
}
