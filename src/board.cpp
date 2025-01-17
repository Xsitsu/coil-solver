#include "board.hpp"

#include <regex>
#include <format>

Board::Board()
{
    
}

Board::Board(std::string puzzle_data)
{
    this->size_x = this->DecodeWidth(puzzle_data);
    this->size_y = this->DecodeHeight(puzzle_data);
    this->tiles = this->DecodeTiles(puzzle_data);
}

std::string Board::ExtractVariable(std::string puzzle_data, std::string var_name) const
{
    std::string base = std::format("var {} = ", var_name);
    std::regex pattern(std::format("{}.*?;", base));
    std::smatch matches;
    std::regex_search(puzzle_data, matches, pattern);

    std::string result;
    for (auto match : matches)
    {
        result += match;
    }

    int start_pos = base.length();
    int new_len = result.length() - start_pos - 1;

    return result.substr(base.length(), new_len);
}

int Board::DecodeWidth(std::string puzzle_data) const
{
    return std::stoi(this->ExtractVariable(puzzle_data, "width"));
}

int Board::DecodeHeight(std::string puzzle_data) const
{
    return std::stoi(this->ExtractVariable(puzzle_data, "height"));

}

std::vector<int> Board::DecodeTiles(std::string puzzle_data) const
{
    std::string tile_data = this->ExtractVariable(puzzle_data, "boardStr");
    return std::vector<int>();
}
