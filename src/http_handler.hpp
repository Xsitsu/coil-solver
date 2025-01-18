#ifndef HTTP_HANDLER_HPP_INCLUDE
#define HTTP_HANDLER_HPP_INCLUDE

#include <string>

class HttpHandler
{
public:
    HttpHandler(std::string username, std::string password);

    std::string GetPuzzleData() const;
    void PostPuzzleSolution() const;

private:
    std::string base_url;
    std::string ConstructBaseUrl(std::string username, std::string password);

    std::string GetWebsiteData() const;

};

#endif // HTTP_HANDLER_HPP_INCLUDE