#ifndef LADYBUGUSERH
#define LADYBUGUSERH

#include <string>
#include <vector>
#include "ladybugobjects.h"


namespace Ladybug
{
  class AWSLadybugConn;

  typedef int UserID;
  typedef int PhotoID;
  typedef std::string CommentID;
  //How deep in the comment response chain the comment is, 0 for root comment
  typedef int CommentChainID;
  typedef int LadybugCredits;

  //Class containing information on a currently loaded user
  class LadybugUser
  {
  public:
    //Used for creating a new user, login token is set to user's session login token
    LadybugUser(std::string email, std::string profname, std::string plaintextPass,
                   PhotoID profilepic, int *logintoken_);
    //Used for loading a user from memory
    LadybugUser(UserID userID, std::string hashedpwd, int *logintoken_);
    Comment GetComment(int index);

    //Saves the user to the database
    void SaveUser(AWSLadybugConn *conn);
    //Removes the user from the database
    void DeleteUser(AWSLadybugConn *conn);
    UserID GetID() { return userid_; }


  private:
    UserID userid_;
    //Token used for authenticating POST requests
    int login_token;
    //User information
    std::string emailaddr;
    std::string profilename;
    char pwhash[42];
    PhotoID profilePicID;
    std::vector<UserID> peopleFollowing;
    std::vector<UserID> followers;
    //List of comment ids stored under this user
    std::vector<CommentID> userComments;


  };

}


#endif
