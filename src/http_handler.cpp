#include "http_handler.hpp"

#include <curl/curl.h>
#include <regex>

HttpHandler::HttpHandler(std::string username, std::string password)
{
    this->base_url = this->ConstructBaseUrl(username, password);
}

std::string HttpHandler::GetPuzzleData() const
{
    std::string website_data = this->GetWebsiteData();
    
    return website_data;
}

std::string HttpHandler::GetWebsiteData() const
{
    CURL *curl = curl_easy_init();
    if (curl == nullptr)
        throw "Curl failed!";

    curl_easy_setopt(curl, CURLOPT_URL, this->base_url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        throw curl_easy_strerror(res);

    curl_easy_cleanup(curl);

    std::string ret = "lmao";

    return ret;
}

void HttpHandler::PostPuzzleSolution() const
{

}

std::string HttpHandler::ConstructBaseUrl(std::string username, std::string password)
{
    std::string base_url = "http://www.hacker.org/coil/index.php";
    std::string creds = "?name=" + username + "&password=" + password;
    std::string url = base_url + creds;
    return url;
}
