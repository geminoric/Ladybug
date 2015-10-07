#include "ladybugobjects.h"

namespace Ladybug
{
  Comment::Comment(CommentID comID, UserID poster, std::string commtext) : id(comID), commentPoster(poster), comment(commtext)
  {
  }
}

