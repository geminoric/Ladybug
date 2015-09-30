#include <iostream>
#include <string>

#define AWSS3HOST "s3-us-west-2.amazonaws.com"

extern "C"
{
#include "aws4c.h"
}



int main()
{
  //Init aws
  aws_init();
  //aws_set_debug(0);
  aws_set_debug(1);//DEBUG MODE

  char *s3Host = AWSS3HOST;
  s3_set_host(s3Host);
  //Get credentials
  char *key = new char[100];
  char *keyid = new char[100];
  std::cin.width(99);
  //Startup message
  std::cout << "Ladybug Backend 0.0.1\nPlease enter your key:";
  std::cin >> key;
  std::cout << "Please enter your keyid:";
  std::cin >> keyid;
  //Set credentials
  aws_set_key(key);
  aws_set_keyid(keyid);

  char *targBucket = "testbucket.tester";
  s3_set_bucket(targBucket);

  return 0;
}
