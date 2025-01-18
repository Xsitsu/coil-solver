#include <iostream>

#include "http_handler.hpp"

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

    try
    {
        std::string dat = handler.GetPuzzleData();
        std::cout << "Got: " << dat << std::endl;
    }
    catch (char const* err)
    {
        std::cout << "Error: " << err << std::endl;
        return -1;
    }

    return 0;
}
