#ifndef LADYBUGOBJECTSCONNH
#define LADYBUGOBJECTSCONNH

#include <string>

typedef int UserID;
typedef int PhotoID;
typedef int CommentID;
//How deep in the comment response chain the comment is, 0 for root comment
typedef int CommentChainID;
typedef int LadybugCredits;

namespace Ladybug
{
  class Comment
  {
  public:
    //Make a new comment
    Comment(UserID poster, std::string commtext, int cid);
    //returns true if comment id is in use
    bool isIDUsed(CommentID comID, UserID userID);
    commentID GetID();

  private:
    CommentID id;
    int chainID;
    UserID commentPoster;
    std::string comment;
  };

}
#endif
