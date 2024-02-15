#include "iostream"
#include <optional>

std::string GetAiMove(std::string brd);

std::optional<std::pair<int, int>> GetBestMoves(char board[3][3], bool maxingPlayerTurn,
                                char player );
