#include <iostream>
#include <curl/curl.h>

int main(void)
{
    CURL *curl = nullptr;
    CURLcode res;

    curl = curl_easy_init();
    if (curl == nullptr) return -1;

    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        fprintf(stderr, "failed! : %s\n",
            curl_easy_strerror(res));

    curl_easy_cleanup(curl);

    return 0;
}
