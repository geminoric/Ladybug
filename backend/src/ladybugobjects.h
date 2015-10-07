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
    Comment(CommentID comID, UserID poster, std::string commtext);

  private:
    CommentID id;
    UserID commentPoster;
    std::string comment;
  };

}
#endif
