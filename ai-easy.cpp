#include "import.h"
#include "sstream"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
using namespace std;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

char *AiMove_easy() {

  stringstream stream;

  srand(time(NULL));
  int col = rand() % 3 + 1;

  int row = rand() % 3 + 1;

  char *resp = new char[2];

  switch (col) {
  case 1:
    resp[0] = 'A';
    break;
  case 2:
    resp[0] = 'B';
    break;
  case 3:
    resp[0] = 'C';
    break;
  }
  switch (row) {
  case 1:
    resp[1] = '1';
    break;
  case 2:
    resp[1] = '2';
    break;
  case 3:
    resp[1] = '3';
    break;
  }
  resp[2] = '\0';

  sleep_for(nanoseconds(10));
  sleep_until(system_clock::now() + seconds(1));

  return resp;
}
