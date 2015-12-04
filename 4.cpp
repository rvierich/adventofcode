#include <iostream>
#include <openssl/md5.h>

static const char hexchars[] = "0123456789abcdef";

int main(void) {

  unsigned int i = 0;

  std::string key = "abcdef";
  std::string data;



  for (int i = 0; i < 100; i++) {
    std::string result;

    data = key + std::to_string(i);


    unsigned char * digest;
    digest = MD5((const unsigned char *)data.c_str(), data.size(), NULL);

    // unsigned char * tmp = digest;
    // std::cout << i << ":";

    // while(tmp) {
    //   std::cout << tmp++;
    // }

    for (int j = 0; j < 16; j++) {
      unsigned char elem = digest[i];

      char hex[3];
      hex[0] = hexchars[elem >> 4];
      hex[1] = hexchars[elem & 0xF];
      hex[2] = 0;

      result.append(hex);
    }

    std::cout << i << "    data: " << data << "    result:" << result << std::endl;
  }
}
