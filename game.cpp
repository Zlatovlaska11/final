#include "ai_import.h"
#include "import.h"
#include <cmath>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>

const std::string red("\033[0;31m");
const std::string reset("\033[0m");

using namespace std;

class Settings {

  struct ArrayWithColors {
    std::string color;
    char boardChar;
  };

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

public:
  ArrayWithColors **ArrayHiglitedWin(char board[3][3], vector<string> pattern) {
    string *ptrn = pattern.data();

    ArrayWithColors **array = new ArrayWithColors *[3];

    for (int i = 0; i < 3; ++i) {
      array[i] = new ArrayWithColors[3];
    }

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

    ArrayWithColors **array = ArrayHiglitedWin(board, coords);

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
};

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
    if (CheckForWin()) {
      PrintLogo();

      cout << "\033[2J\033[1;1H";

      PrintLogo();

      Settings set;

      set.PrintHiglitedBoard(board, (round % 2 != 0) ? 'X' : 'O');

    } else {
      DisplayBoard(board);
    }

    cout << '\n';
    if (isBoardFull()) {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "ITS A DRAW";
    } else if (round % 2 == 0) {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "PLAYER 2 WON";
    } else {
      cout << string((getConsoleWidth() / 2) - 5, ' ') << "PLAYER 1 WON";
    }

    cout << '\n'
         << string((getConsoleWidth() / 2) - 10, ' ')
         << "Press Enter To continue";

    initscr();

    curs_set(0);

    keypad(stdscr, TRUE);

    cbreak();

    getch();

    endwin();

    cout << "\033[2J\033[1;1H";

    if (playagain()) {
      cout << "\033[2J\033[1;1H";
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
