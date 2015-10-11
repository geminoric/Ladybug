#include <iostream>
#include <string>
#include <string.h>
#include <signal.h>
#include <onion/log.h>
#include <onion/onion.h>
#include <onion/shortcuts.h>
#include <alloca.h>
#include "ladybugusersconn.h"

char AMAZONS3HOST[] = "s3-us-west-1.amazonaws.com";
char USERBUCKET[] = "ladybugusers";

#define DEBUGMODE 1

extern "C"
{
#include "aws4c.h"
}


int main()
{
  srand(time(0));
  //AWS INIT
  aws_init();
  aws_set_debug(0);
  //aws_set_debug(1);//DEBUG MODE

  s3_set_host(AMAZONS3HOST);
  //Get credentials
  char *key = new char[100];
  char *keyid = new char[100];
  std::cin.width(99);
  //Startup message
  std::cout << "Ladybug Backend 0.0.1\nEnter your authentication key:";
  std::cin >> key;
  std::cout << "Enter your keyid:";
  std::cin >> keyid;
  //Set credentials
  aws_set_key(key);
  aws_set_keyid(keyid);

  s3_set_bucket(USERBUCKET);
  //AWS INIT OVER

  Ladybug::AWSLadybugConn AWSConnection;

  //test create a user
  int logintoken = 0;
  //Ladybug::LadybugUser testusr("testemail@test.com", "Raymond", "password", 42, &logintoken);
  //testusr.SaveUser(&AWSConnection);
  


  return 0;
}

