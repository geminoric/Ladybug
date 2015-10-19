#include "ladybugobjects.h"
#include "ladybugusersconn.h"
#include <stdlib.h>

namespace Ladybug
{
  //Make a new comment
  Comment::Comment(UserID poster, std::string commtext) : chainID(cid), id(comID), commentPoster(poster), comment(commtext)
  {
    //Create random comment IDs until one is available
    int cID = -1;
    while
    {
      id = rand();
    }(isIDUsed(id, poster));

  }

  //returns true if comment id is in use
  bool Comment::isIDUsed(int comID, int userID)
  {
    for(int i = 0;i < AWSLadybugConn::userComments.size();++i)
    {
      if(AWSLadybugConn::GetUser(userID)->GetComment(i).GetID() == comID)return true;
    }
    return false;
  }

  Comment::GetID() { return id; }
}

