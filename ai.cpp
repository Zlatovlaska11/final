#include "import.h"
#include <string>

using namespace std;
class Ai {
private:
  char board[3][3];
  bool _IsFisrt;
  int _round;

  string Mover(int moveRow, int moveCol) {

    if (_round == 1 && _IsFisrt) {
      return "20";
    }
    return 0;
  }

public:
  Ai(bool isFirst, int round) {
    this->_IsFisrt = isFirst;
    this->_round = round;
  }
};

char board[3][3];
bool _IsFisrt = true;
int _round = 1;

string Mover(int moveRow, int moveCol) {

  if (_round == 1 && _IsFisrt) {
    return "20";
  }
  return 0;
}
