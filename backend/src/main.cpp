#include "DDBInterface.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

int main()
{
  curl_global_init(CURL_GLOBAL_ALL);
  //Curl testing
  Ladybug::AmazonDynDBConn test;

  std::string str;
  std::string target("TESTAMAZONTARGET");
  test.FormCanonicalRequest(&str, &target, 10);

  std::cout << str << std::endl;

  return 0;
}
