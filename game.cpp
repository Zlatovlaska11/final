#include "import.h"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;
class Game {

public:
  char board[3][3] = {{'#', '#', '#'}, {'#', '#', '#'}, {'#', '#', '#'}};

  void PrintBoard() {

    int width = getConsoleWidth() / 2;
    cout << string(width - 3, ' ');
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cout << board[i][j] << ' ';
      }
      cout << '\n';
      cout << string(width - 3, ' ');
    }
  }

  int getConsoleWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
  }

  void GetMove(char player, bool isItPLayerTurn) {
    PrintLogo();
    PrintBoard();
    cout << endl;
    string _move;

    if (isItPLayerTurn) {

      string text = "your move: ";
      cout << string(((getConsoleWidth() / 2) - sizeof(sizeof(text))), ' ') +
                  "insert your move: ";

      cin >> _move;

      while (!CanPlay(_move)) {
        cout << "invalid move select another: ";

        cin >> _move;
      }
    } else {
      _move = (string)AiMove_easy();
      while (!CanPlay(_move)) {
        _move = (string)AiMove_easy();
      }
    }

    int row;
    switch (_move[0]) {
    case 'A':
      row = 0;
      break;
    case 'B':
      row = 1;
      break;
    case 'C':
      row = 2;
      break;
    case 'a':
      row = 0;
      break;
    case 'b':
      row = 1;
      break;
    case 'c':
      row = 2;
      break;
    }

    int col;
    switch (_move[1]) {
    case '1':
      col = 0;
      break;
    case '2':
      col = 1;
      break;
    case '3':
      col = 2;
      break;
    default:
      break;
    }

    board[row][col] = player;

    cout << "\033[2J\033[1;1H";
  }

  bool CanPlay(string &move) const {
    int row, col;

    switch (move[0]) {
    case 'A':
      row = 0;
      break;
    case 'B':
      row = 1;
      break;
    case 'C':
      row = 2;
      break;
    case 'a':
      row = 0;
      break;
    case 'b':
      row = 1;
      break;
    case 'c':
      row = 2;
      break;
    default:
      return false; // Invalid row
    }

    switch (move[1]) {
    case '1':
      col = 0;
      break;
    case '2':
      col = 1;
      break;
    case '3':
      col = 2;
      break;
    default:
      return false; // Invalid column
    }

    return board[row][col] == '#'; // Check if the position is empty
  }

  bool CheckForWin() {
    for (int i = 0; i < 3; ++i) {
      if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
           board[i][0] != '#') ||
          (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
           board[0][i] != '#')) {
        return true;
      }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
         board[0][0] != '#') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
         board[0][2] != '#')) {
      return true;
    }

    return false;
  }

  void GameLoop() {
    int round = 0;

    bool didSomeOneWin = CheckForWin();
    while (!didSomeOneWin) {

      if (round % 2 == 0) {
        // IMPORTANT //
        // false if is computers move but have to finish this shit
        GetMove('X', true);
      } else {
        GetMove('o', false);
      }
      round++;
      didSomeOneWin = CheckForWin();
    }
    if (round % 2 == 0) {
      cout << "PLAYER 2 WON";
    } else {
      cout << "player 1 won";
    }
  }

  // write a method to check for win and calculate which sign to place in the
  // array by counting the rounds and deviding by two
};

void StartGame() {
  Game game;
  game.GameLoop();
}
