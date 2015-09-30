#include "DDBInterface.h"
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <alloca.h>
#include <ctime>

#define AMAZONDYNDBHOST "dynamodb.us-west-2.amazonaws.com"
#define AMAZONCONTENTTYPE "application/x-amz-json-1.0"
#define AMAZONCONNECTIONTYPE "Keep-Alive"

namespace Ladybug
{
  //Puts data from curl into userdata string
  size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
  {
    *(static_cast<std::string *>(userdata)) = ptr;
    //Return total data used (all of it)
    return size * nmemb;
  }

  AmazonDynDBConn::AmazonDynDBConn() : curl_(curl_easy_init()), DynDBHost(AMAZONDYNDBHOST)
  {
  }

  //Returns true if contents gotten
  bool AmazonDynDBConn::GetContents(std::string *contents, const char *name_)
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
  bool AmazonDynDBConn::CreateDatabase(const char *name_)
  {
    std::cout << name_;
    return true;
  }

  //Form header for canonical request
  void AmazonDynDBConn::FormHeader(std::string *header, std::string *amz_target,
                                    int content_length)
  {
    //Length of the data as a string for use later
    std::string data_length;
    //Temporary buffer for sprintf
    char *temp_ccp = static_cast<char *>(alloca(100));
    sprintf(temp_ccp, "%i", content_length);
    data_length = temp_ccp;

    time_t curtime;
    time(&curtime);
    tm *gmtTime = gmtime(&curtime);
    //Format amz_date
    sprintf(temp_ccp, "%04i%02i%02iT%02i%02i%02iZ", gmtTime->tm_year + 1900, gmtTime->tm_mon + 1,
                gmtTime->tm_mday, gmtTime->tm_hour, gmtTime->tm_min, gmtTime->tm_sec);
    //Used to store date and time
    std::string amz_date = temp_ccp;

    *header = "POST / HTTP/1.1\nhost: ";
    *header += DynDBHost;
    *header += "\nx-amz-date: ";
    *header += amz_date + "\nx-amz-target: " + *amz_target + '\n';
    //*header += authorization
    *header += "content-type: ";
    *header += AMAZONCONTENTTYPE;
    //*header += '\n';
    *header += "\ncontent-length: ";
    *header += data_length;
    *header += "\nconnection: ";
    *header += AMAZONCONNECTIONTYPE;
  }

  //Form body for canonical request
  void AmazonDynDBConn::FormBody(std::string *body)
  {
    *body = "";
  }

  bool AmazonDynDBConn::MakeTestPOSTRequest()
  {

    return true;
  }

  //Creates canonical request for use in creating auth signatuer
  void AmazonDynDBConn::FormCanonicalRequest(std::string *request, std::string *amz_target,
                                    int content_length)
  {
    //Temporary buffer for sprintf
    char *temp_ccp = static_cast<char *>(alloca(100));

    time_t curtime;
    time(&curtime);
    tm *gmtTime = gmtime(&curtime);
    //Format amz_date
    sprintf(temp_ccp, "%04i%02i%02iT%02i%02i%02iZ", gmtTime->tm_year + 1900, gmtTime->tm_mon + 1,
                gmtTime->tm_mday, gmtTime->tm_hour, gmtTime->tm_min, gmtTime->tm_sec);
    //Used to store date and time
    std::string amz_date = temp_ccp;

    //Format date stamp

    //Date without time
    std::string date_stamp;

    //Length of the data as a string for use later
    sprintf(temp_ccp, "%i", content_length);
    std::string data_length = temp_ccp;

    *request = "POST https://";
    *request += AMAZONDYNDBHOST;
    *request += "/ HTTP/1.1\n";
    *request += "Host: ";
    *request += AMAZONDYNDBHOST;
    *request += "\nContent-Length: ";
    *request += data_length;
    *request += "\nContent-Type: ";
    *request += AMAZONCONTENTTYPE;
    *request += "\nX-Amz-Date: ";
    *request += amz_date;
    *request += '\n';
  }

  //Forms autorization signature used in POST header
  void AmazonDynDBConn::FormAuthorizationSignature(std::string *signature)
  {
    *signature = "";
  }
}
