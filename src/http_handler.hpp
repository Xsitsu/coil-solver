#ifndef HTTP_HANDLER_HPP_INCLUDE
#define HTTP_HANDLER_HPP_INCLUDE

#include <string>

class HttpHandler
{
public:
    HttpHandler(std::string username, std::string password, std::string cache_directory_path);

    std::string GetPuzzleData(int level) const;
    void PostPuzzleSolution() const;

private:
    std::string base_url;

private:
    std::string ConstructBaseUrl(std::string username, std::string password);

    std::string GetWebsiteData(int level) const;
    std::string ExtractPuzzleData(std::string website_data, int level) const;

    // Necessary because of how CURL works.
    static size_t curl_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);


// TODO: Extract this stuff out into its own class
private:
    std::string cache_directory_path;
    bool using_cache;

private:
    void SetupCache(std::string cache_directory_path);
    bool CacheExists(std::string cache_directory_path) const;
    void CreateCache(std::string cache_directory_path) const;
    bool CanUseCache(std::string cache_directory_path) const;
    std::string GetCacheFilePathForLevel(int level) const;
    bool HasLevelInCache(int level) const;
    std::string ReadPuzzleDataFromCache(int level) const;
    void WritePuzzleDataToCache(int level, std::string puzzle_data) const;

};

#endif // HTTP_HANDLER_HPP_INCLUDE