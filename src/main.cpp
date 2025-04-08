#include <iostream>
#include <string>

#include "http/http_handler.hpp"
#include "board.hpp"
#include "board_preprocessor.hpp"

void output_board(Board b)
{
    std::cout << "Width: " << b.GetSizeX() << std::endl;
    std::cout << "Height: " << b.GetSizeY() << std::endl;
    std::cout << "Tiles:\n" << b.GetTilesStr() << std::endl;
}

void usage(std::string prog_name)
{
    std::cout << "Usage: " + prog_name + " <username> <password> <level_number>" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc <= 3)
    {
        usage(argv[0]);
        return -1;
    }

    std::string username = argv[1];
    std::string password = argv[2];

    int level = 25;
    if (argc <= 4)
    {
        level = std::stoi(argv[3]);
    }


    HttpHandler handler(username, password, "./level-cache/");

    std::string puzzle_data;

    try
    {
        puzzle_data = handler.GetPuzzleData(level);
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


    BoardPreprocessor proc;
    Board chokepoints = proc.DetectChokepoints(board);
    output_board(chokepoints);

    Board t_juncs = proc.DetectTJunctions(board);
    output_board(t_juncs);

    return 0;
}
