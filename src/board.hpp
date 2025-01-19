#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <string>

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

private:
    int size_x;
    int size_y;
    int *tiles;

private:
    std::string ExtractVariable(std::string puzzle_data, std::string var_name) const;

    int DecodeWidth(std::string puzzle_data) const;
    int DecodeHeight(std::string puzzle_data) const;
    int* DecodeTiles(std::string puzzle_data) const;

private:
    void CleanupTiles();
};

#endif // BOARD_HPP_INCLUDE