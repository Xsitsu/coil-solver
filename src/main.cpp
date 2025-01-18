#include <iostream>

#include "http_handler.hpp"
#include "board.hpp"

void output_var(std::string puzzle_data, std::string var_name)
{
    Board board;
    std::cout << var_name << ": '" << board.ExtractVariable(puzzle_data, var_name) << "'" << std::endl << std::endl;
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

    Board board(puzzle_data);

    std::cout << "Width: " << board.GetSizeX() << std::endl;
    std::cout << "Height: " << board.GetSizeY() << std::endl;
    std::cout << "Tiles:\n" << board.GetTilesStr() << std::endl;
    
    //output_var(puzzle_data, "width");
    //output_var(puzzle_data, "height");
    //output_var(puzzle_data, "boardStr");

    return 0;
}
