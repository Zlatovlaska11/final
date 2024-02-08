#include "import.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curses.h>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#define Red "\033[31m"
#define RESET "\033[0m"

using namespace std;

class Base {

  int getConsoleWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
  }

public:
  void PrintTextInTheMiddle(string text, bool highlight) {

    int consoleWidth = getConsoleWidth();

    int leadingSpaces = (consoleWidth - text.length()) / 2;

    // Print the centered text
    if (highlight) {

      cout << Red;
    }
    std::cout << std::setw(leadingSpaces + text.length()) << text << std::endl
              << std::endl;

    cout << RESET;
  }

private:
  string options[4] = {"Easy PC", "Hard PC", "2 Player Mode"};

  void PrintHiglighted(int selection, int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
      if (selection == i) {
        PrintTextInTheMiddle(options[i], true);
      } else {
        PrintTextInTheMiddle(options[i], false);
      }
    }
  }

public:
  void PrintTitle() {

    string title[8] = {
        "  ______ _             _   _____           _           _   ",
        " |  ____(_)           | | |  __ \\         (_)         | |  ",
        " | |__   _ _ __   __ _| | | |__) | __ ___  _  ___  ___| |_ ",
        " |  __| | | '_ \\ / _` | | |  ___/ '__/ _ \\| |/ _ \\/ __| __|",
        " | |    | | | | | (_| | | | |   | | | (_) | |  __/ (__| |_ ",
        " |_|    |_|_| |_|\\__,_|_| |_|   |_|  \\___/| |\\___|\\___|\\__|",
        "                                         _/ |              ",
        "                                        |__/               "};

    int consoleWidth = getConsoleWidth();
    for (size_t i = 0; i < 8; i++)
      cout << string(50, ' ') + title[i] << endl;
  }

  int PrintFullMenu() {

    int arrayLength = sizeof(options) / sizeof(string);
    int currentSelection = 0;
    char keypress = 80;
    do {
      PrintTitle();

      PrintHiglighted(currentSelection, arrayLength);

      cout << RESET;

      initscr();

      curs_set(0);

      keypad(stdscr, TRUE);

      cbreak();

      keypress = getch();

      // End the ncurses mode
      endwin();

      if (keypress == 's') {
        if (currentSelection == arrayLength - 1) {
          currentSelection -= currentSelection;
        } else {
          currentSelection++;
        }
      } else if (keypress == 'w') {
        if (currentSelection == 0) {
          currentSelection += arrayLength - 1;
        } else {

          currentSelection--;
        }
      } else if (keypress == '\n' && keypress != EOF) {
        return currentSelection + 1;
      }

      system("clear");
    } while (true);
  }
};
class Select {
private:
  int selection;

public:
  Select(int selection) { this->selection = selection; };

  void Selector() {
    if (selection < 4) {
      cout << "\033[2J\033[1;1H";
      StartGame(selection);
    } else {
      // add settings to select board theme and after game higliting
    }
  }
};

void CallWholeMenu() {
  Base base;

  int selection = base.PrintFullMenu();

  Select select(selection);

  select.Selector();
}

int main(int argc, char *argv[]) {

  CallWholeMenu();

  return 0;
}
void PrintInDaMiddle(string text) {
  Base base;
  base.PrintTextInTheMiddle(text, false);
}

void PrintLogo() {
  Base base;
  base.PrintTitle();
}
