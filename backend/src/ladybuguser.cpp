#include "ladybuguser.h"
#include "ladybugusersconn.h"
#include "sha1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <iostream>
#include <vector>


namespace Ladybug
{
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
    vecToData(photos, photoids);

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
