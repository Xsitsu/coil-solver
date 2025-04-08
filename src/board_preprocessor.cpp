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

    if (this->TileIsWall(top_tile))
    {
        if (this->TileIsBlocker(bottom_tile))
            return true;

       if (this->TileIsWall(board.GetTile(x - 1, y + 1)))
            return true;

        if (this->TileIsWall(board.GetTile(x + 1, y + 1)))
            return true;
    }
    else if (this->TileIsWall(bottom_tile))
    {
        if (this->TileIsVoid(top_tile))
            return true;
        
        if (this->TileIsWall(board.GetTile(x - 1, y - 1)))
            return true;

        if (this->TileIsWall(board.GetTile(x + 1, y - 1)))
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

    if (this->TileIsWall(left_tile))
    {
        if (this->TileIsBlocker(right_tile))
            return true;

       if (this->TileIsWall(board.GetTile(x + 1, y - 1)))
            return true;

        if (this->TileIsWall(board.GetTile(x + 1, y + 1)))
            return true;
    }
    else if (this->TileIsWall(right_tile))
    {
        if (this->TileIsVoid(left_tile))
            return true;

        if (this->TileIsWall(board.GetTile(x - 1, y - 1)))
            return true;

        if (this->TileIsWall(board.GetTile(x - 1, y + 1)))
            return true;
    }

    return false;
}

bool BoardPreprocessor::TileIsVoid(const Tile *tile) const
{
    return (tile == nullptr);
}

bool BoardPreprocessor::TileIsWall(const Tile *tile) const
{
    if (tile != nullptr)
        return tile->IsWall();
    return false;
}

bool BoardPreprocessor::TileIsBlocker(const Tile *tile) const
{
    return (tile == nullptr || tile->IsWall());
}
