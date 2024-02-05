#include <cstring>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<int, int>>
getPossibleMoves(const std::vector<std::vector<int>> &board) {
  std::vector<std::pair<int, int>> possibleMoves;

  // Iterate through the board to find empty positions
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == 0) { // Assuming 0 represents an empty cell
        possibleMoves.push_back(std::make_pair(i, j));
      }
    }
  }

  return possibleMoves;
}

int main(int argc, char *argv[]) {
  // std::cout << "┌───────────────────┐";
  // std::cout << "│                   │";
  std::string str = "12";
  int i = str[0] - '0';

  std::string board[3][3] = {{"#", "#", "X"}, {"X", "X", "O"}, {"X", "X", "O"}};
  std::string(*ptrBoard)[3];
  ptrBoard = board;
  std::vector<std::vector<int>> exampleBoard = {
      {1, 0, 2}, {0, 1, 2}, {2, 1, 0}};

  std::vector<std::pair<int, int>> moves = getPossibleMoves(exampleBoard);

  std::cout << "Possible Moves:\n";
  for (const auto &move : moves) {
    std::cout << "(" << move.first << ", " << move.second << ")\n";
  }

  return 0;
}
