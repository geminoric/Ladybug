#ifndef DDBINTERFACE_H
#define DDBINTERFACE_H

#include <string>

typedef void CURL;

namespace Ladybug
{
  //Returns true if contents gotten
  bool GetContents(std::string *contents, const char *name_);
  bool GetContents(std::string *contents, const char *name_, CURL *curl_);
  //Return true on success
  bool CreateDatabase(const char *name_);

}


#endif