#include "random"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

void Move() {
  srand(time(NULL));
  int col = rand() % 3 + 1;

  int row = rand() % 3 + 1;

  cout << col;

  cout << row;
}

int main(int argc, char *argv[]) {
  Move();
  return 0;
}
