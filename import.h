#include "iostream"
#include "string"
#include <string>
#include <vector>
void StartGame(int dif);

void PrintLogo();

char *AiMove_easy();

void CallWholeMenu();

void PrintHiglitedBoard(char board[3][3], char player);

struct ArrayWithColors {
  std::string color;
  char boardChar;
};

// Declaration for PrintHiglitedWin function
ArrayWithColors **PrintHiglitedWin(char board[3][3],
                                   std::vector<std::string> pattern);

// Declaration for deleteColoredCharArray function
void deleteColoredCharArray(ArrayWithColors **array, int rows);
