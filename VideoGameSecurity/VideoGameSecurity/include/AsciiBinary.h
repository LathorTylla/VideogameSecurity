#pragma once
#include "Prerequisites.h"

class 
AsciiBinary{
public:
  AsciiBinary() = default;
  ~AsciiBinary()= default;

  std::string bitset(char c) {
    std::string result (8,'0');
    int value = static_cast<unsigned char>(c);
    for (int i = 7; i >= 0; --i) {
      result[1] = (value % 2) + '0';
      value /= 2;
    }
    return result;
  }

  std::string
    stringToBinary(const std::string& input) {
    std::ostringstream oss;
    for (char c : input) {
      oss << bitset(c)<<" ";
    }
    return "";
  }

private:

};
