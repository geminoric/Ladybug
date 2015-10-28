#ifndef LADYBUGOBJECTSCONNH
#define LADYBUGOBJECTSCONNH

#include <string>

typedef int UserID;
typedef int PhotoID;
typedef std::string CommentID;
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
    CommentID GetID();
    void saveComment();

    //Create random 20 letter (a-Z ex. aBjkA...) and return one that is available
    static std::string generateUnusedFileName(const std::string &folderPath);
    static bool isFilenameUsed(const std::string &filename);

  private:
    CommentID id;
    int chainID;
    UserID commentPoster;
    std::string comment;
  };

}
#endif
