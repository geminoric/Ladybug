#ifndef LADYBUGUSERSCONNH
#define LADYBUGUSERSCONNH
#include "ladybuguser.h"
#include <map>
#include <string>

namespace Ladybug
{
  //So sorry this is public and global, please don't modify it without other functions
  extern std::map<int, Ladybug::LadybugUser *> loadedUsers;
  //Used as a interface for accessing ladybug functions
  class AWSLadybugConn
  {
  public:
    AWSLadybugConn();
    //Returns data from a user id file, given a parameter to search for, such as pwhash:
    static std::string GetDataFromUserIDFile(int userID, std::string searchTerm);
    static int SetDataToFile(std::string filePathName, std::string data);
    static int DeleteFile(std::string filePathName);
    static int ReadFile(std::string filePathName, std::string *data);
    //Increments the user ID for the next new user
    static void incrementNextUserID();
    static void AddUserToSystem(LadybugUser usr);

    //Load a user into the system
    static int LoadUser(std::string email, std::string plainttextpwd);
    
    //Current amount of total users, used for giving new user ids, MAKE SURE TO UPDATE DURING SERVER INIT
    static int nextUserID;

  private:

  };

}
#endif
