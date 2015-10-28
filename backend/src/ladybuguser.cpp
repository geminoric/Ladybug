#include "ladybuguser.h"
#include "ladybugusersconn.h"
#include "sha1.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <iostream>
#include <vector>


namespace Ladybug
{
  //Function assumes userID is valid
  //Returns data from a user id file, given a parameter to search for, such as pwhash:
  std::string AWSLadybugConn::GetDataFromUserIDFile(int userID, std::string searchTerm)
  {
    //Read in user id file
    std::string data;
    char *id = (char *)alloca(50);
    sprintf(id, "Users/%i", userID);
    AWSLadybugConn::ReadFile(id, &data);
    //Position in file of hashed password
    int hashPos = data.find(searchTerm) + searchTerm.size() - 1;
    //Find how much data until end of line
    int i = 0;
    char buffer[200];
    while(data[hashPos + ++i] != '\n')
    {
      //Load each character into the buffer
      buffer[i - 1] = data[hashPos + i];
    }
    buffer[i - 1] = 0;

    return buffer;
  }
  //Used for user authentication, returns true if authenticated
  //This function assumes userid file already exists
  bool authenticateUser(int userID, std::string hashedpwd)
  {
    if(AWSLadybugConn::GetDataFromUserIDFile(userID, "pwhash:") == hashedpwd)return true;
    return false;
  }

  LadybugUser::LadybugUser(std::string email, std::string profname, std::string plaintextPass,
                   PhotoID profilepic, int *logintoken_)
                :   emailaddr(email), profilename(profname), profilePicID(profilepic),
                    userid_(AWSLadybugConn::nextUserID)
 {
    //Hash the user's password
    unsigned char tempHashStorage[20];
    //Salt the plaintext password with the user's userID
    char *saltedPlaintext = (char *)alloca(50);
    sprintf(saltedPlaintext, "%i", userid_);
    strcat(saltedPlaintext, plaintextPass.c_str());
    //Hash the salted password
    sha1::calc(saltedPlaintext,  strlen(saltedPlaintext), tempHashStorage);
    sha1::toHexString(tempHashStorage, pwhash);
    pwhash[42] = 0;
    //Create the login token
    login_token = rand();
    //Return the token to the user
    *logintoken_ = login_token;
    AWSLadybugConn::incrementNextUserID();
    //Add user to ladybugusers vector
    AWSLadybugConn::AddUserToSystem(*this);
 }

  //Used for loading a user from memory
  //logintoken_ used for error codes
  //-1  : User not found
  //-2  : Authentication error
  LadybugUser::LadybugUser(int userID, std::string hashedpwd, int *logintoken_) : userid_(userID)
  {
    std::string data;
    char *id = (char *)alloca(50);
    sprintf(id, "Users/%i", userID);
    //Return -1 if the user's file was not found
    if(AWSLadybugConn::ReadFile(id, &data))
    {
      *logintoken_ = -1;
      return;
    }
    //Authenticate user
    if(!authenticateUser(userID, hashedpwd))
    {
      *logintoken_ = -2;
      return;
    }

    //Load all the user's data
    emailaddr = AWSLadybugConn::GetDataFromUserIDFile(userID, "email:");
    profilename = AWSLadybugConn::GetDataFromUserIDFile(userID, "profname:");
    std::string profID = AWSLadybugConn::GetDataFromUserIDFile(userID, "profpicID:");
    profilePicID = atoi(profID.c_str());

    //IMPORTANT - ADD FUNCTIONS HERE TO IMPORT DATA INTO THE VECTORS

    login_token = rand();
    *logintoken_ = login_token;

    //Add user to ladybugusers vector
    AWSLadybugConn::AddUserToSystem(*this);
  }

  void vecToData(std::vector<int> &vec, char *data)
  {
    data[0] = 0;
    for(int i = 0; i < vec.size();++i)
    {
      //Covnert int to string so it can be added
      char *intstring = (char *)alloca(20);
      sprintf(intstring, "%i", vec[i]);
      strcat(data, intstring);
      //Add data to seperate each vector component
      strcat(data, ":");
    }
  }
  void vecToData(std::vector<std::string> &vec, char *data)
  {
    data[0] = 0;
    for(int i = 0;i < vec.size();++i)
    {
      strcat(data, vec[i].c_str());
      //Add data to seperate each vector component
      strcat(data, ":");
    }
  }

/*
  //Return comment with filename, assume user is authenticated
  Comment LadybugUser::GetComment(int index)
  {
    return userComments[index];
  }*/

  //Saves the user to the database
   void LadybugUser::SaveUser(AWSLadybugConn *conn)
   {
    //Getting data from vectors to be saved
    char *peoFollowing = (char *)alloca(10000);
    char *peoFollowers = (char *)alloca(10000);
    char *comments = (char *)alloca(10000);
    char *photoids = (char *)alloca(10000);

    //Load all the data
    vecToData(peopleFollowing, peoFollowing);
    vecToData(followers, peoFollowers);
    vecToData(userComments, comments);

    char *dataToSave = (char *)alloca(1000);
    //Create data format to be saved
    sprintf(dataToSave, "email:%s\nprofname:%s\npwhash:%s\nprofpicID:%i\npeoplefollowing:%s\nfollowers:%s\ncomments:%s\nphotoids:%s\n", 
                        emailaddr.c_str(), profilename.c_str(), pwhash,
                        profilePicID, peoFollowing, peoFollowers, comments,
                        photoids);

    //Save user
    char *filePath = (char *)alloca(100);
    sprintf(filePath, "Users/%i", userid_);
    conn->SetDataToFile(filePath, dataToSave);

  }

}
