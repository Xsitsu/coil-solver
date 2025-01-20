#include "board.hpp"

#include <regex>
#include <format>
#include <cstring>

Board::Board() : size_x(0), size_y(0), tiles(nullptr)
{
    
}

Board::Board(std::string puzzle_data) : size_x(0), size_y(0), tiles(nullptr)
{
    this->LoadPuzzleData(puzzle_data);
}

Board::Board(const Board& other)
{
    this->size_x = other.size_x;
    this->size_y = other.size_y;

    int num_tiles = other.GetNumTiles();
    this->tiles = new int[num_tiles];
    memcpy(this->tiles, other.tiles, num_tiles * sizeof(int));
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
        bool tile_is_valid = ((cur_tile & Board::TileDirection::Valid) == Board::TileDirection::Valid);
        if (tile_is_valid)
        {
            int count = 0;
            if ((cur_tile & Board::TileDirection::Up) != 0) count++;
            if ((cur_tile & Board::TileDirection::Right) != 0) count++;
            if ((cur_tile & Board::TileDirection::Down) != 0) count++;
            if ((cur_tile & Board::TileDirection::Left) != 0) count++;

            tile_str += std::to_string(count);
        }
        else
            tile_str += "W";
    }
    return tile_str;
}

int Board::GetTileUp(int tile_index) const
{
    int new_index = tile_index - this->size_x;
    if (new_index < 0)
        return -1;

    return new_index;
}

int Board::GetTileDown(int tile_index) const
{
    int new_index = tile_index + this->size_x;
    if (new_index >= this->GetNumTiles())
        return -1;

    return new_index;
}

int Board::GetTileLeft(int tile_index) const
{
    if (this->IsLeftEdge(tile_index))
        return -1;

    return tile_index - 1;
}

int Board::GetTileRight(int tile_index) const
{
    if (this->IsRightEdge(tile_index))
        return -1;

    return tile_index + 1;
}

bool Board::IsLeftEdge(int tile_index) const
{
    return (tile_index % this->size_x == 0);
}

bool Board::IsRightEdge(int tile_index) const
{
    return (tile_index % this->size_x == size_x - 1);
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
    memset(t, Board::TileDirection::Init, tile_len * sizeof(int));

    for (int i = 0; i < tile_len; i++)
    {
        char cur_tile_str = tile_data.c_str()[i + 1];
        if (cur_tile_str == 'X')
        {
            t[i] &= ~(Board::TileDirection::Valid);

            int new_index;

            new_index = this->GetTileUp(i);
            if (new_index >= 0)
                t[new_index] -= Board::TileDirection::Down;

            new_index = this->GetTileDown(i);
            if (new_index >= 0)
                t[new_index] -= Board::TileDirection::Up;

            new_index = this->GetTileLeft(i);
            if (new_index >= 0)
                t[new_index] -= Board::TileDirection::Right;

            new_index = this->GetTileRight(i);
            if (new_index >= 0)
                t[new_index] -= Board::TileDirection::Left;
        }
    }

    return t;
}
