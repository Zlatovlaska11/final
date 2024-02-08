#include "ai_import.h"
#include "import.h"
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>

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

  pair<int, int> ConvertMove(string move) {

    pair<int, int> Moves;

    switch (move[0]) {
    case 'A':
      Moves.first = 0;
      break;
    case 'B':
      Moves.first = 1;
      break;
    case 'C':
      Moves.first = 2;
      break;
    case 'a':
      Moves.first = 0;
      break;
    case 'b':
      Moves.first = 1;
      break;
    case 'c':
      Moves.first = 2;
      break;
    }

    switch (move[1]) {
    case '1':
      Moves.second = 0;
      break;
    case '2':
      Moves.second = 1;
      break;
    case '3':
      Moves.second = 2;
      break;
    default:
      break;
    }
    return Moves;
  }
  void GetMove(char player, bool isItPLayerTurn, int dificulty) {
    PrintLogo();
    DisplayBoard(board);
    cout << endl;
    string _move;

    int row;
    int col;

    if (isItPLayerTurn || dificulty == 3) {
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

      pair<int, int> moves = ConvertMove(_move);

      row = moves.first;
      col = moves.second;

    } else {
      if (dificulty == 2) {
        pair<int, int> move = GetBestMove(board, true, player);
        row = move.first;
        col = move.second;
      } else if (dificulty == 1) {
        _move = AiMove_easy();
        while (!CanPlay(_move)) {
          _move = AiMove_easy();
        }
        pair<int, int> moves = ConvertMove(_move);

        row = moves.first;
        col = moves.second;
      }
    }

    board[row][col] = player;

    cout << "\033[2J\033[1;1H";
  }

  bool CanPlay(string &move) {
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

    cout << '\n' << string(width - 10, ' ') << text;

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

  void GameLoop(int dif) {
    int round = 0;

    bool didSomeOneWin = CheckForWin();
    while (!didSomeOneWin) {
      if (round % 2 == 0) {
        if (isBoardFull()) {
          break;
        }
        GetMove('X', true, dif);
      } else {
        GetMove('O', false, dif);
      }
      round++;
      didSomeOneWin = CheckForWin();
    }
    PrintLogo();

    cout << '\n';
    if (isBoardFull()) {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "ITS A DRAW";
    } else if (round % 2 == 0) {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "PLAYER 2 WON";
    } else {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "PLAYER 1 WON";
    }

    //! ADD BOARD HIGHLIGHTING AFTER WIN TO SHOW HOW WIN WAS ACHIEVD

    cout << '\n'
         << string((getConsoleWidth() / 2) - 10, ' ')
         << "Press Enter To continue";

    initscr();

    curs_set(0);

    keypad(stdscr, TRUE);

    cbreak();

    getch();

    endwin();

    PrintHiglitedBoard(board, (round % 2 == 0) ? 'X' : 'O');

    cout << "\033[2J\033[1;1H";

    if (playagain()) {
      ResetBoard(board);
      GameLoop(dif);
    } else {
      cout << "\033[2J\033[1;1H";
      CallWholeMenu();
    }
  }
};

void StartGame(int dif) {
  Game game;
  game.GameLoop(dif);
}
