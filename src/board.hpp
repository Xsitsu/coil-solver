#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <string>
#include <vector>

class Board
{
public:
    Board();
    Board(std::string puzzle_data);

public:
    int size_x;
    int size_y;
    std::vector<int> tiles;

public:
    std::string ExtractVariable(std::string puzzle_data, std::string var_name) const;

    int DecodeWidth(std::string puzzle_data) const;
    int DecodeHeight(std::string puzzle_data) const;
    std::vector<int> DecodeTiles(std::string puzzle_data) const;
};

#endif // BOARD_HPP_INCLUDE