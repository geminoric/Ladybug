#include "DDBInterface.h"
#include <curl/curl.h>
#include <iostream>

void function_pt(char *ptr, size_t size, size_t nmemb, void *stream)
{
    std::cout << ptr << std::endl;
}

int main()
{
  //Curl testing
  CURL *curl;
  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "www.google.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }


  return 0;
}
