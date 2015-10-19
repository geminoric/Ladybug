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
    static std::string GetDataFromUserIDFile(int userID, std::string searchTerm);
    //Returns -1 if failed to find email
    static int GetUserIDFromEmail(std::string email_);
    static int SetDataToFile(std::string filePathName, std::string data);
    static int DeleteFile(std::string filePathName);
    static int ReadFile(std::string filePathName, std::string *data);
    static LadybugUser* GetUser(int userID);
    //Increments the user ID for the next new user
    static void incrementNextUserID();
    static void AddUserToSystem(LadybugUser &usr);

    //Load a user into the system, returns -1 on fail, otherwise userID
    static int LoadUser(std::string email, std::string plaintextpwd, int *logintoken__);
    
    //Current amount of total users, used for giving new user ids, MAKE SURE TO UPDATE DURING SERVER INIT
    static int nextUserID;

  private:

  };

}
#endif
