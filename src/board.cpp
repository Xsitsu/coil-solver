#include "board.hpp"

#include <regex>
#include <format>

#include <iostream>

Board::Board() : size_x(0), size_y(0), tiles(nullptr)
{
    
}

Board::Board(std::string puzzle_data) : size_x(0), size_y(0), tiles(nullptr)
{
    this->LoadPuzzleData(puzzle_data);
}

Board::~Board()
{
    this->size_x = 0;
    this->size_y = 0;
    this->CleanupTiles();
}

int Board::GetSizeX() const
{
    return this->size_x;
}

int Board::GetSizeY() const
{
    return this->size_y;
}

int Board::GetNumTiles() const
{
    return this->GetSizeX() * this->GetSizeY();
}

std::string Board::GetTilesStr() const
{
    std::string tile_str;
    int num_tiles = this->GetNumTiles();
    for (int i = 0; i < num_tiles; i++)
    {
        if (i % this->GetSizeX() == 0 && i != 0)
            tile_str += "\n";

        int cur_tile = this->tiles[i];
        if (cur_tile == 1)
            tile_str += "W";
        else if (cur_tile == 0)
            tile_str += "_";
    }
    return tile_str;
}

void Board::LoadPuzzleData(std::string puzzle_data)
{
    this->CleanupTiles();

    this->size_x = this->DecodeWidth(puzzle_data);
    this->size_y = this->DecodeHeight(puzzle_data);
    this->tiles = this->DecodeTiles(puzzle_data);
}

void Board::CleanupTiles()
{
    if (this->tiles != nullptr)
    {
        delete[] this->tiles;
        this->tiles = nullptr;
    }
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

int* Board::DecodeTiles(std::string puzzle_data) const
{
    std::string tile_data = this->ExtractVariable(puzzle_data, "boardStr");

    int tile_len = tile_data.length() - 2;

    int *t = new int[tile_len];

    for (int i = 0; i < tile_len; i++)
    {
        char cur_tile_str = tile_data.c_str()[i + 1];
        if (cur_tile_str == 'X')
            t[i] = 1;
        else if (cur_tile_str == '.')
            t[i] = 0;
    }

    return t;
}
