#include "DDBInterface.h"
#include <string>
#include <iostream>
#include <curl/curl.h>

namespace Ladybug
{
  //Puts data from curl into userdata string
  size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
  {
    *(static_cast<std::string *>(userdata)) = ptr;
    //Return total data used (all of it)
    return size * nmemb;
  }

  //Returns true if contents gotten
  bool GetContents(std::string *contents, const char *name_)
  {
    CURL *curl_;
    curl_ = curl_easy_init();
    if(curl_)
    {
      curl_easy_setopt(curl_, CURLOPT_URL, name_);
      curl_easy_setopt(curl_, CURLOPT_WRITEDATA, contents);
      curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
      if(curl_easy_perform(curl_))return false;
      curl_easy_cleanup(curl_);
      return true;
    }
    return false;
  }

  //Does not create or destroy curl object
  bool GetContents(std::string *contents, const char *name_, CURL *curl_)
  {
    if(curl_)
    {
      curl_easy_setopt(curl_, CURLOPT_URL, name_);
      curl_easy_setopt(curl_, CURLOPT_WRITEDATA, contents);
      curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
      if(curl_easy_perform(curl_))return false;
      return true;
    }
    return false;
  }

  //Return true on success
  bool CreateDatabase(const char *name_)
  {
    std::cout << name_;
    return true;
  }
}
