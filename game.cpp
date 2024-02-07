#include "ai_import.h"
#include "import.h"
#include <curses.h>
#include <exception>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;
class Game {
private:
  char board[3][3] = {{'#', '#', '#'}, {'#', '#', '#'}, {'#', '#', '#'}};
  string boardAsString;

public:
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

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == ' ') {
          board[i][j] = '#';
        }
      }
    }
  }

  void BoardToString() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        boardAsString += board[i][j];
      }
    }
  }

  int getConsoleWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
  }

  void GetMove(char player, bool isItPLayerTurn) {
    PrintLogo();
    DisplayBoard(board);
    cout << endl;
    string _move;

    int row;
    int col;

    if (isItPLayerTurn) {
      // add selection ai by accepting one more parameter name dificulty and
      // deciding by this
      const string text = "inert your move: ";
      cout << string(((getConsoleWidth() / 2) - sizeof(sizeof(text))), ' ')
           << text;

      cin >> _move;

      while (!CanPlay(_move)) {
        cout << "\033[2J\033[1;1H";
        PrintLogo();
        DisplayBoard(board);
        cout << '\n'
             << string((getConsoleWidth() / 2) - 12, ' ')
             << "invalid move select another: ";
        cin >> _move;
      }

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
    } else {
      pair<int, int> move = GetBestMove(board, true, player);
      row = move.first;
      col = move.second;
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
  bool isBoardFull() {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (board[i][j] == '#') {
          return false; // Board is not full
        }
      }
    }
    return true; // Board is full
  }

  bool playagain() {

    int width = getConsoleWidth() / 2;

    cout << "\033[2J\033[1;1H";

    string text = "wanna play again: ";

    PrintLogo();

    char selection;

    cout << string(width - text.length(), ' ') << text;

    cin >> selection;

    return (selection == 'y') ? true : false;
  }

  void ResetBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = '#';
      }
    }
  }

  void GameLoop() {
    int round = 0;

    bool didSomeOneWin = CheckForWin();
    while (!didSomeOneWin) {
      if (round % 2 == 0) {
        if (isBoardFull()) {
          break;
        }
        GetMove('X', true);
      } else {
        GetMove('O', false);
      }
      round++;
      didSomeOneWin = CheckForWin();
    }
    PrintLogo();

    if (isBoardFull()) {

      cout << string(getConsoleWidth() / 2, ' ') << "ITS A DRAW";
    } else if (round % 2 == 0) {
      cout << string(getConsoleWidth() / 2, ' ') << "PLAYER 2 WON";
    } else {
      cout << string(getConsoleWidth() / 2, ' ') << "player 1 won";
    }
    sleep((double)0.5);

    if (playagain()) {
      ResetBoard(board);
      cout << "\033[2J\033[1;1H";
      GameLoop();
    }
  }
  // write a method to check for win and calculate which sign to place in the
  // array by counting the rounds and deviding by two
};

void StartGame() {
  Game game;
  game.GameLoop();
}
