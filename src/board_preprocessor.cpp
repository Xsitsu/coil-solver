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
            bool set_val = false;
            if (this->HasWallTopAndBottom(to_process, i) || this->HasWallLeftAndRight(to_process, i))
            {
                set_val = true;
            }

            set_tile->SetConnectionUp(set_val);
            set_tile->SetConnectionDown(set_val);
            set_tile->SetConnectionLeft(set_val);
            set_tile->SetConnectionRight(set_val);
        }
    }

    return b;
}

bool BoardPreprocessor::HasWallTopAndBottom(const Board &board, int tile_index) const
{
    return this->HasWallDoubleGeneric(
        board.GetTileUp(tile_index),
        board.GetTileDown(tile_index)
    );
}

bool BoardPreprocessor::HasWallLeftAndRight(const Board &board, int tile_index) const
{
    return this->HasWallDoubleGeneric(
        board.GetTileLeft(tile_index),
        board.GetTileRight(tile_index)
    );
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
