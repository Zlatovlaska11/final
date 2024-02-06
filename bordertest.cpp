#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 0 && j == 0) {
        cout << "╔";
      } else if (i == 2 && j == 0) {
        cout << "╗";
      } else if (i == 0 && j % 2 == 0) {
        cout << "╦";
      } else if (i != 0 && j % 2 == 0) {
        cout << "╬";
      } else {
        cout << "══";
      }
    }
    cout << '\n';
  }
  return 0;
}
