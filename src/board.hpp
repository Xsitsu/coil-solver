#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <string>
#include <list>

class Board
{
public:
    enum TileDirection
    {
        None = 0,

        Up = 1,
        Right = 2,
        Down = 4,
        Left = 8,

        All = 15,

        Valid = 16,

        Init = 31,
    };

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
    void FloodFill(int tile_index, int num_cons, Board &processed, Board& island) const;

    bool IsTileIndexInBounds(int tile_index) const;

    void SetTile(int tile_index, int value);

    int GetTile(int tile_index) const;
    int GetTileUp(int tile_index) const;
    int GetTileDown(int tile_index) const;
    int GetTileLeft(int tile_index) const;
    int GetTileRight(int tile_index) const;

    int GetTileIndexUp(int tile_index) const;
    int GetTileIndexDown(int tile_index) const;
    int GetTileIndexLeft(int tile_index) const;
    int GetTileIndexRight(int tile_index) const;


    bool IsLeftEdge(int tile_index) const;
    bool IsRightEdge(int tile_index) const;
    bool IsTopEdge(int tile_index) const;
    bool IsBottomEdge(int tile_index) const;

    std::list<Board> GetIslands() const;


private:
    int size_x;
    int size_y;
    int num_tiles;
    int *tiles;

private:
    std::string ExtractVariable(std::string puzzle_data, std::string var_name) const;

    int DecodeWidth(std::string puzzle_data) const;
    int DecodeHeight(std::string puzzle_data) const;
    int* DecodeTiles(std::string puzzle_data) const;

private:
    void CleanupTiles();

    int GetTileGeneric(int tile_index) const;
};

#endif // BOARD_HPP_INCLUDE
