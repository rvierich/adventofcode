#include <iostream>
#include <openssl/md5.h>


#define MD5_DIGEST_LENGTH 16

static const char hexchars[] = "0123456789abcdef";


std::string convertDigestToHexString(unsigned char * digest) {
  std::string result;

  for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    unsigned char elem = digest[i];

    char hex[3];
    hex[0] = hexchars[elem >> 4];
    hex[1] = hexchars[elem & 0xF];
    hex[2] = 0;

    result.append(hex);
  }

  return result;
}



bool hasSixZeroes(unsigned char * digest) {
  unsigned char testNumber[16] = {0xFF, 0xFF, 0xFF, 0x00,
                                  0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00};

  unsigned char andResult = 0;
  for (int j = 0; j < MD5_DIGEST_LENGTH; j++) {
    andResult = testNumber[j] & digest[j];
    if (andResult) return false;
  }

  return true;
}

int main(void) {
  std::string key = "ckczppom";
  std::string data;

  unsigned int i = 0;
  bool _hasFiveZeroes = false;
  unsigned char * digest;

  while (!_hasFiveZeroes) {
    data = key + std::to_string(i);

    digest = MD5((const unsigned char *)data.c_str(), data.size(), NULL);
    _hasFiveZeroes = hasSixZeroes(digest);

    ++i;
  }

  std::string result = convertDigestToHexString(digest);

  std::cout << i-1 << "    data: " << data << "    result:" << result << std::endl;
  std::cout << "has 5 zeroes: " << _hasFiveZeroes << std::endl;
}
