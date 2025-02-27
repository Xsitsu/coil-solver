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
    this->num_tiles = other.num_tiles;

    int num_tiles = other.GetNumTiles();
    this->tiles = new Tile[num_tiles];
    memcpy(this->tiles, other.tiles, num_tiles * sizeof(Tile));
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
    return this->num_tiles;
}

std::string Board::GetTilesStr() const
{
    std::string tile_str;
    int num_tiles = this->GetNumTiles();
    for (int i = 0; i < num_tiles; i++)
    {
        if (i % this->GetSizeX() == 0 && i != 0)
            tile_str += "\n";

        Tile &cur_tile = this->tiles[i];
        if (!cur_tile.IsWall())
        {
            int count = 4 - cur_tile.GetNumberWalls();
            tile_str += std::to_string(count);
        }
        else
            tile_str += "W";

        tile_str += " ";
    }
    return tile_str;
}

bool Board::IsTileIndexInBounds(int tile_index) const
{
    return (tile_index >= 0 && tile_index < this->GetNumTiles());
}

Tile* Board::GetTile(int x, int y)
{
    return this->GetTile(this->XYCoordToTileIndex(x, y));
}

Tile* Board::GetTile(int tile_index)
{
    if (this->IsTileIndexInBounds(tile_index))
        return &(this->tiles[tile_index]);

    return nullptr;
}

int Board::GetTileIndexUp(int tile_index) const
{
    int new_index = tile_index - this->size_x;
    if (new_index < 0)
        return -1;

    return new_index;
}

int Board::GetTileIndexDown(int tile_index) const
{
    int new_index = tile_index + this->size_x;
    if (new_index >= this->GetNumTiles())
        return -1;

    return new_index;
}

int Board::GetTileIndexLeft(int tile_index) const
{
    if (this->IsLeftEdge(tile_index))
        return -1;

    return tile_index - 1;
}

int Board::GetTileIndexRight(int tile_index) const
{
    if (this->IsRightEdge(tile_index))
        return -1;

    return tile_index + 1;
}

Tile* Board::GetTileUp(int tile_index)
{
    return this->GetTile(this->GetTileIndexUp(tile_index));
}

Tile* Board::GetTileDown(int tile_index)
{
    return this->GetTile(this->GetTileIndexDown(tile_index));
}

Tile* Board::GetTileLeft(int tile_index)
{
    return this->GetTile(this->GetTileIndexLeft(tile_index));
}

Tile* Board::GetTileRight(int tile_index)
{
    return this->GetTile(this->GetTileIndexRight(tile_index));
}

const Tile* Board::GetTile(int x, int y) const
{
    return this->GetTile(this->XYCoordToTileIndex(x, y));
}

const Tile* Board::GetTile(int tile_index) const
{
    if (this->IsTileIndexInBounds(tile_index))
        return &(this->tiles[tile_index]);

    return nullptr;
}

const Tile* Board::GetTileUp(int tile_index) const
{
    return this->GetTile(this->GetTileIndexUp(tile_index));
}


const Tile* Board::GetTileDown(int tile_index) const
{
    return this->GetTile(this->GetTileIndexDown(tile_index));
}


const Tile* Board::GetTileLeft(int tile_index) const
{
    return this->GetTile(this->GetTileIndexLeft(tile_index));
}


const Tile* Board::GetTileRight(int tile_index) const
{
    return this->GetTile(this->GetTileIndexRight(tile_index));
}

bool Board::IsLeftEdge(int tile_index) const
{
    return (tile_index % this->size_x == 0);
}

bool Board::IsRightEdge(int tile_index) const
{
    return (tile_index % this->size_x == size_x - 1);
}

bool Board::IsTopEdge(int tile_index) const
{
    return (tile_index < this->size_x);
}

bool Board::IsBottomEdge(int tile_index) const
{
    return (this->num_tiles - tile_index < this->size_x);
}

int Board::TileIndexToXCoord(int tile_index) const
{
    return (tile_index % this->GetSizeX());
}

int Board::TileIndexToYCoord(int tile_index) const
{
    return (tile_index / this->GetSizeX());
}

int Board::XYCoordToTileIndex(int x, int y) const
{
    int index = x + (y * this->GetSizeX());
    if (index >= 0 && index < this->GetNumTiles())
        return index;

    return -1;
}

void Board::LoadPuzzleData(std::string puzzle_data)
{
    this->CleanupTiles();

    this->DecodeWidth(puzzle_data);
    this->DecodeHeight(puzzle_data);
    this->num_tiles = this->size_x * this->size_y;
    this->DecodeTiles(puzzle_data);
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

void Board::DecodeWidth(std::string puzzle_data)
{
    this->size_x = std::stoi(this->ExtractVariable(puzzle_data, "width"));
}

void Board::DecodeHeight(std::string puzzle_data)
{
    this->size_y = std::stoi(this->ExtractVariable(puzzle_data, "height"));
}

void Board::DecodeTiles(std::string puzzle_data)
{
    this->CleanupTiles();

    std::string tile_data = this->ExtractVariable(puzzle_data, "boardStr");

    int tile_len = tile_data.length() - 2;

    this->tiles = new Tile[tile_len];

    for (int i = 0; i < tile_len; i++)
    {
        Tile *cur_tile = this->GetTile(i);

        char cur_tile_str = tile_data.c_str()[i + 1];
        if (cur_tile_str == 'X')
        {
            cur_tile->SetIsWall();

            Tile *other_tile = nullptr;

            other_tile = this->GetTileUp(i);
            if (other_tile != nullptr)
                other_tile->SetConnectionDown(false);

            other_tile = this->GetTileDown(i);
            if (other_tile != nullptr)
                other_tile->SetConnectionUp(false);

            other_tile = this->GetTileLeft(i);
            if (other_tile != nullptr)
                other_tile->SetConnectionRight(false);

            other_tile = this->GetTileRight(i);
            if (other_tile != nullptr)
                other_tile->SetConnectionLeft(false);
        }
        else
        {
            if (this->IsLeftEdge(i))
               cur_tile->SetConnectionLeft(false);
            if (this->IsRightEdge(i))
                cur_tile->SetConnectionRight(false);
            if (this->IsBottomEdge(i))
                cur_tile->SetConnectionDown(false);
            if (this->IsTopEdge(i))
                cur_tile->SetConnectionUp(false);
        }
    }
}

