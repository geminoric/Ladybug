#ifndef DDBINTERFACE_H
#define DDBINTERFACE_H

#include <string>

typedef void CURL;

namespace Ladybug
{
  //NOTE : Call curl_global_init(CURL_GLOBAL_ALL) before use
  class AmazonDynDBConn
  {
  public:
    AmazonDynDBConn();
    //Returns true if contents gotten
    bool GetContents(std::string *contents, const char *name_);
    //Return true on success
    bool CreateDatabase(const char *name_);
    void FormHeader(std::string *header, std::string *amz_target,
                                    int content_length);

  private:
    //Form header for canonical request
    //void FormHeader(std::string *header, std::string *amz_target,
    //                                int content_length);
    //Form body for canonical request
    void FormBody(std::string *body);
    bool MakeTestPOSTRequest();
    //Forms autorization signature used in POST header
    void FormAuthorizationSignature(std::string *signature);
    //Creates canonical request for use in creating auth signatuer
    void FormCanonicalRequest(std::string *request, std::string *amz_date, int content_length);

    CURL *curl_;
    std::string DynDBHost;
  };

}


#endif