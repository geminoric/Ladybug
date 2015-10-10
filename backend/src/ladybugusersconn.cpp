#include "ladybugusersconn.h"
#include "ladybuguser.h"
#include <string>

extern "C"
{
#include "aws4c.h"
}

namespace Ladybug
{

  int AWSLadybugConn::nextUserID = 0;

  AWSLadybugConn::AWSLadybugConn()
  {
    //Count how many users have been created and set it to the next user ID
    nextUserID = 0;
  }


  //Functions return the return value from network operation
  //Sets a file to the data, creates a new file if one doesn't exist
  //Returns 0 on success
  int AWSLadybugConn::SetDataToFile(std::string filePathName, std::string data)
  {
    IOBuf *buffer = aws_iobuf_new();
    char *passData = const_cast<char *>(data.c_str());
    char *fileName = const_cast<char *>(filePathName.c_str());
    aws_iobuf_append(buffer, passData, data.size());
    int ret = s3_put(buffer, fileName);
    aws_iobuf_free(buffer);
    return ret;
  }

  //Delete file from the currently open bucket
  //Returns 0 on success
  int AWSLadybugConn::DeleteFile(std::string filePathName)
  {
    IOBuf *buffer = aws_iobuf_new();
    char *fileName = const_cast<char *>(filePathName.c_str());
    int ret = s3_delete(buffer, fileName);
    aws_iobuf_free(buffer);
    return ret;
  }

  //Read from a file from the currently open bucket
  //Returns 0 on success
  int AWSLadybugConn::ReadFile(std::string filePathName, std::string *data)
  {
    data->clear();
    IOBuf *buffer = aws_iobuf_new();
    char *fileName = const_cast<char *>(filePathName.c_str());
    int ret = s3_get(buffer, fileName);
    while(true)
    {
      //Read in 1024 bytes at a time
      char ln[1024];
      int bytesRead = aws_iobuf_getline(buffer, ln, sizeof(ln));
      *data += ln;
      //Break if file is done being read
      if(ln[0] == 0) break;
    }

    aws_iobuf_free(buffer);
    return ret;
  }
}
