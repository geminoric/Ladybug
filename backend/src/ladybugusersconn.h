#ifndef LADYBUGUSERSCONNH
#define LADYBUGUSERSCONNH
#include "ladybuguser.h"
#include <map>
#include <string>

namespace Ladybug
{
  //Used as a interface for accessing ladybug functions
  class AWSLadybugConn
  {
  public:
    AWSLadybugConn();
    int SetDataToFile(std::string filePathName, std::string data);
    int DeleteFile(std::string filePathName);
    int ReadFile(std::string filePathName, std::string *data);


  private:
    std::map<int, Ladybug::LadybugUser> loadedUsers;
    //Current amount of total users, used for giving new user ids, MAKE SURE TO UPDATE DURING SERVER INIT
    int nextUserID;

  };

}
#endif
