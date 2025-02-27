#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <string>
#include <list>

#include "tile.hpp"

class Board
{
public:
    Board();
    Board(std::string puzzle_data);
    Board(const Board& other);

    ~Board();

    void LoadPuzzleData(std::string puzzle_data);

    int GetSizeX() const;
    int GetSizeY() const;
    int GetNumTiles() const;
    std::string GetTilesStr() const;

    bool IsTileIndexInBounds(int tile_index) const;

    Tile* GetTile(int tile_index);
    Tile* GetTileUp(int tile_index);
    Tile* GetTileDown(int tile_index);
    Tile* GetTileLeft(int tile_index);
    Tile* GetTileRight(int tile_index);

    const Tile* GetTile(int tile_index) const;
    const Tile* GetTileUp(int tile_index) const;
    const Tile* GetTileDown(int tile_index) const;
    const Tile* GetTileLeft(int tile_index) const;
    const Tile* GetTileRight(int tile_index) const;

    int GetTileIndexUp(int tile_index) const;
    int GetTileIndexDown(int tile_index) const;
    int GetTileIndexLeft(int tile_index) const;
    int GetTileIndexRight(int tile_index) const;

    bool IsLeftEdge(int tile_index) const;
    bool IsRightEdge(int tile_index) const;
    bool IsTopEdge(int tile_index) const;
    bool IsBottomEdge(int tile_index) const;

    int TileIndexToXCoord(int tile_index) const;
    int TileIndexToYCoord(int tile_index) const;
    int XYCoordToTileIndex(int x, int y) const;

private:
    int size_x;
    int size_y;
    int num_tiles;
    Tile *tiles;

private:
    std::string ExtractVariable(std::string puzzle_data, std::string var_name) const;

    void DecodeWidth(std::string puzzle_data);
    void DecodeHeight(std::string puzzle_data);
    void DecodeTiles(std::string puzzle_data);

private:
    void CleanupTiles();
};

#endif // BOARD_HPP_INCLUDE
