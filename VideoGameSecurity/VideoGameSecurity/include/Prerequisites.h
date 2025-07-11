#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <functional>
#include <stdexcept>
#include <random>
#include <fstream> 

#include <mutex>
#include <array>

struct 
SensitiveData {
  std::string user;
  std::string password;
  std::string others;
};