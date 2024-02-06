#include "iostream"

std::string GetAiMove(std::string brd);

std::pair<int, int> GetBestMove(char board[3][3], bool maxingPlayerTurn,
                                char player);
