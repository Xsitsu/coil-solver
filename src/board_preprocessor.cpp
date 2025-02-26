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

    int tunnel_val = Board::TileDirection::All && Board::TileDirection::Valid;
    int non_val = Board::TileDirection::Valid;

    int num_tiles = to_process.GetNumTiles();
    for (int i = 0; i < num_tiles; i++)
    {
        if (!(this->TileIsWall(i)))
        {
            if (this->HasWallTopAndBottom(to_process, i) || this->HasWallLeftAndRight(to_process, i))
            {
                b.SetTile(i, tunnel_val);
            }
            else
            {
                b.SetTile(i, non_val);
            }
        }
    }

    return b;
}

bool BoardPreprocessor::HasWallTopAndBottom(const Board &board, int tile_index) const
{
    int tile_1 = board.GetTileUp(tile_index);
    int tile_2 = board.GetTileDown(tile_index);

    return (this->TileIsWall(tile_1) && this->TileIsWall(tile_2));
}

bool BoardPreprocessor::HasWallLeftAndRight(const Board &board, int tile_index) const
{
    int tile_1 = board.GetTileLeft(tile_index);
    int tile_2 = board.GetTileRight(tile_index);

    return (this->TileIsWall(tile_1) && this->TileIsWall(tile_2));
}

bool BoardPreprocessor::TileIsWall(int tile) const
{
    return (tile == -1) || ((tile & Board::TileDirection::Valid) != Board::TileDirection::Valid);
}
