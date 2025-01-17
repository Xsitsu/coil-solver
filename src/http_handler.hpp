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
    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

};

#endif // HTTP_HANDLER_HPP_INCLUDE