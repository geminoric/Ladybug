#include <iostream>
#include <string>
#include <string.h>
#include <signal.h>
#include <onion/log.h>
#include <onion/onion.h>
#include <onion/shortcuts.h>
#include <alloca.h>

char AMAZONS3HOST[] = "s3-us-west-1.amazonaws.com";
char TESTBUCKET[] = "testbucket.testerey";

extern "C"
{
#include "aws4c.h"
}

//Answers POST with "text", checks if HEAD, if so writes it, if not prints data
onion_connection_status post_data(void *_, onion_request *req, onion_response *res){
  if (onion_request_get_flags(req)&OR_HEAD){
    onion_response_write_headers(res);
    return OCS_PROCESSED;
  }
  const char *user_data=onion_request_get_post(req,"text");
  onion_response_printf(res, "The user wrote: %s", user_data);
  return OCS_PROCESSED;
}

//The onion object
onion *o=NULL;

void onexit(int _){
  ONION_INFO("Exit");
  if (o)
    onion_listen_stop(o);
}



int main()
{
  //onion http testing
  o=onion_new(O_ONE_LOOP);
  onion_url *urls=onion_root_url(o);
  onion_set_port(o, "420");
  
  onion_url_add_static(urls, "", 
  "<html>\n"
  "<head>\n"
  " <title>Simple post example</title>\n"
  "</head>\n"
  "\n"
  "Write something: \n"
  "<form method=\"POST\" action=\"data\">\n"
  "<input type=\"text\" name=\"text\">\n"
  "<input type=\"submit\">\n"
  "</form>\n"
  "\n"
  "</html>\n", HTTP_OK);

  onion_url_add(urls, "data", (void *)post_data);

  signal(SIGTERM, onexit);  
  signal(SIGINT, onexit); 
  onion_listen(o);

  onion_free(o);

  /*
  aws_init();
  //aws_set_debug(0);
  aws_set_debug(1);//DEBUG MODE

  s3_set_host(AMAZONS3HOST);
  //Get credentials
  char *key = new char[100];
  char *keyid = new char[100];
  std::cin.width(99);
  //Startup message
  std::cout << "Ladybug Backend 0.0.1\nPlease enter your key:";
  std::cin >> key;
  std::cout << key << std::endl;
  std::cout << "Please enter your keyid:";
  std::cin >> keyid;
  //Set credentials
  aws_set_key(key);
  aws_set_keyid(keyid);

  //Test stuff
  s3_set_bucket(TESTBUCKET);
  IOBuf *bf = aws_iobuf_new();
  for(int i = 0;i < 100;++i)
  {
    char s[] = "helllo";
    aws_iobuf_append(bf, s, strlen(s));
  }
  char thing[] = "testfile.test";
  int returnval = s3_put(bf, thing);
  std::cout << "Return Value: " << returnval << std::endl;
  */

  return 0;
}
