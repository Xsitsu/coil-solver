#ifndef BOARD_PREPROCESSOR_HPP_INCLUDE
#define BOARD_PREPROCESSOR_HPP_INCLUDE

#include "board.hpp"

class BoardPreprocessor
{
public:
    BoardPreprocessor();

    Board DetectChokepoints(const Board &to_process) const;

private:
    bool HasWallTopAndBottom(const Board &board, int tile_index) const;
    bool HasWallLeftAndRight(const Board &board, int tile_index) const;

};

#endif //BOARD_PREPROCESSOR_HPP_INCLUDE
