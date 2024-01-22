#include "ai_import.h"
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

class Ai_Hard {
private:
  char *moves = new char[3];
  char board[3][3];
  bool FirstMove;

public:
  Ai_Hard(string board) {
    int x = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        this->board[i][j] = board[x];
        x++;
      }
    }
  }
  ~Ai_Hard() { free(moves); }

  bool isFirstMove() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] != '#') {
          return false;
        } else {
          return true;
        }
      }
    }
    return true;
  }

  void SelectionOfMove() {
    if (isFirstMove()) {
      moves[0] = 'A';
      moves[1] = '1';

      moves[2] = '\0';
    } else {
    }
  }
  char *ReturnMove() { return moves; }
};

int main(int argc, char *argv[]) {
  Ai_Hard hard("#########");
  hard.SelectionOfMove();
  cout << (string)hard.ReturnMove();
  return 0;
}
