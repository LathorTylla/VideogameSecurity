#pragma once
#include "Prerequisites.h"

class XOREncoder
{
public:
  XOREncoder() = default;
  ~XOREncoder() = default;

  std::string
    encode(const std::string& imput, const std::string& key) {
    std::string output = imput;
    for (size_t i = 0; i < imput.size(); ++i) {
      output[i] = imput[i] ^ key[i % key.size()];
    }
    return output;
  }

  std::vector<unsigned char>
    Hex
private:

};