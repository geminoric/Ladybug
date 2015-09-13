#include "DDBInterface.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

int main()
{
  curl_global_init(CURL_GLOBAL_ALL);
  //Curl testing
  std::string foo;
  Ladybug::GetContents(&foo, "www.google.com");
  std::cout << foo << std::endl;

  return 0;
}
