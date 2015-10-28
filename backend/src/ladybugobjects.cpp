#include "ladybugobjects.h"
#include "ladybugusersconn.h"
#include <stdlib.h>
#include <stdio.h>

namespace Ladybug
{
  //Make a new comment
  Comment::Comment(UserID poster, std::string commtext, int cid) : chainID(cid), id(generateUnusedFileName("Comments/")), commentPoster(poster), comment(commtext)
  {
    saveComment();
  }

  void Comment::saveComment()
  {

  }

  CommentID Comment::GetID() { return id; }

  //Check if a filename is in use
  bool Comment::isFilenameUsed(const std::string &filename)
  {
    std::string fileData;
    return !AWSLadybugConn::ReadFile(filename, &fileData);
  }

  //Create random 20 letter (a-Z ex. aBjkA...) and return one that is available
  std::string Comment::generateUnusedFileName(const std::string &folderPath)
  {
    std::string name;
    do
    {
      name = folderPath;
      for(int i = 0;i < 21;++i)
      {
        char letter = rand() % 26 + 65;
        //50% chance to make uppercase
        if(rand() % 2)letter += 32;
        name += letter;
      }
    }while(isFilenameUsed(name));

    return name;
  }
}

