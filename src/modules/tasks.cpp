#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <vector>

class Task {
public:
  std::string name;
  std::chrono::seconds startTime;
  std::chrono::seconds endTime;
  int startImportance = 0;
  int endImportance = 100;
  double importance;
};
