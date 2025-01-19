#include <iostream>

#include "http_handler.hpp"
#include "board.hpp"

void output_board(Board b)
{
    std::cout << "Width: " << b.GetSizeX() << std::endl;
    std::cout << "Height: " << b.GetSizeY() << std::endl;
    std::cout << "Tiles:\n" << b.GetTilesStr() << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Need 3 args!!" << std::endl;
        return -1;
    }

    std::string username = argv[1];
    std::string password = argv[2];

    HttpHandler handler(username, password);

    std::string puzzle_data;

    try
    {
        puzzle_data = handler.GetPuzzleData(25);
        std::cout << "Got: " << puzzle_data << std::endl;
    }
    catch (char const* err)
    {
        std::cout << "Error: " << err << std::endl;
        return -1;
    }

    Board board2(puzzle_data);
    Board board(board2);
    output_board(board);

    return 0;
}
