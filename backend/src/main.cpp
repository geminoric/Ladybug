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

  //Load auth data
  aws_set_key((char *)"");
  aws_set_keyid((char *)"");


  //Startup message
  /*std::cout << "Ladybug Backend 0.0.1\nEnter your authentication key:";
  std::cin >> key;
  std::cout << "Enter your keyid:";
  std::cin >> keyid;*/
  //Set credentials
 /* aws_set_key(key);
  aws_set_keyid(keyid);*/

  s3_set_bucket(USERBUCKET);
  //AWS INIT OVER

  Ladybug::AWSLadybugConn AWSConnection;
  //test load a user
  int logintoken;
  AWSConnection.LoadUser("testemail1@test.com", "password1", &logintoken);
  std::cout << "Login token: " << logintoken << std::endl;

  /*Ladybug::LadybugUser testusr("testemail1@test.com", "Raymond1", "password1", 42, &logintoken);
  testusr.SaveUser(&AWSConnection);
  Ladybug::LadybugUser testusr1("testemail2@test.com", "Raymond2", "password2", 42, &logintoken);
  testusr1.SaveUser(&AWSConnection);
  Ladybug::LadybugUser testusr2("testemail3@test.com", "Raymon3", "password3", 42, &logintoken);
  testusr2.SaveUser(&AWSConnection);*/

  


  return 0;
}

