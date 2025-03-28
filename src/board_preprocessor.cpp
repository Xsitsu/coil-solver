#include "board_preprocessor.hpp"

#include <iostream>
#include <string>

BoardPreprocessor::BoardPreprocessor()
{

}

Board BoardPreprocessor::DetectChokepoints(const Board &to_process) const
{
    std::cout << "DetectChokepoints!" << std::endl;
    Board b(to_process);

    int num_tiles = to_process.GetNumTiles();
    for (int i = 0; i < num_tiles; i++)
    {
        const Tile *cur_tile = to_process.GetTile(i);
        if (!(cur_tile->IsWall()))
        {
            Tile *set_tile = b.GetTile(i);
            if (this->HasWallTopAndBottom(to_process, i) || this->HasWallLeftAndRight(to_process, i))
            {
                set_tile->SetIsChokepoint();
            }

            set_tile->SetConnectionUp(set_tile->IsChokepoint());
            set_tile->SetConnectionDown(set_tile->IsChokepoint());
            set_tile->SetConnectionLeft(set_tile->IsChokepoint());
            set_tile->SetConnectionRight(set_tile->IsChokepoint());
        }
    }

    return b;
}

Board BoardPreprocessor::DetectTJunctions(const Board &to_process) const
{
    std::cout << "DetectTJunctions!" << std::endl;
    Board b(to_process);

    int num_tiles = to_process.GetNumTiles();
    for (int i = 0; i < num_tiles; i++)
    {
        const Tile *cur_tile = to_process.GetTile(i);
        if (!(cur_tile->IsWall()))
        {
            Tile *set_tile = b.GetTile(i);
            if (cur_tile->GetNumberConnections() == 3)
            {
                set_tile->SetIsChokepoint();
            }

            set_tile->SetConnectionUp(set_tile->IsChokepoint());
            set_tile->SetConnectionDown(set_tile->IsChokepoint());
            set_tile->SetConnectionLeft(set_tile->IsChokepoint());
            set_tile->SetConnectionRight(set_tile->IsChokepoint());
        }
    }

    return b;
}

bool BoardPreprocessor::HasWallTopAndBottom(const Board &board, int tile_index) const
{
    int x = board.TileIndexToXCoord(tile_index);
    int y = board.TileIndexToYCoord(tile_index);

    const Tile *top_tile = board.GetTileUp(tile_index);
    const Tile *bottom_tile = board.GetTileDown(tile_index);

    if (this->TileIsBlocker(top_tile))
    {
        if (this->TileIsBlocker(bottom_tile))
            return true;

       if (this->TileIsBlocker(board.GetTile(x - 1, y + 1)))
            return true;

        if (this->TileIsBlocker(board.GetTile(x + 1, y + 1)))
            return true;
    }
    else if (this->TileIsBlocker(bottom_tile))
    {
        if (this->TileIsBlocker(board.GetTile(x - 1, y - 1)))
            return true;

        if (this->TileIsBlocker(board.GetTile(x + 1, y - 1)))
            return true;
    }

    return false;
}

bool BoardPreprocessor::HasWallLeftAndRight(const Board &board, int tile_index) const
{
    int x = board.TileIndexToXCoord(tile_index);
    int y = board.TileIndexToYCoord(tile_index);

    const Tile *left_tile = board.GetTileLeft(tile_index);
    const Tile *right_tile = board.GetTileRight(tile_index);

    if (this->TileIsBlocker(left_tile))
    {
        if (this->TileIsBlocker(right_tile))
            return true;

       if (this->TileIsBlocker(board.GetTile(x + 1, y - 1)))
            return true;

        if (this->TileIsBlocker(board.GetTile(x + 1, y + 1)))
            return true;
    }
    else if (this->TileIsBlocker(right_tile))
    {
        if (this->TileIsBlocker(board.GetTile(x - 1, y - 1)))
            return true;

        if (this->TileIsBlocker(board.GetTile(x - 1, y + 1)))
            return true;
    }

    return false;
}

bool BoardPreprocessor::HasWallDoubleGeneric(const Tile *tile1, const Tile *tile2) const
{
    bool tile1_wall = true;
    bool tile2_wall = true;

    if (tile1 != nullptr && !tile1->IsWall())
        tile1_wall = false;

    if (tile2 != nullptr && !tile2->IsWall())
        tile2_wall = false;

    return (tile1_wall && tile2_wall);
}

bool BoardPreprocessor::TileIsBlocker(const Tile *tile) const
{
    return (tile == nullptr || tile->IsWall());
}
