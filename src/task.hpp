#pragma once

#include <chrono>
#include <string>

class Task {
public:
  std::string name;
  std::chrono::seconds startTime;
  std::chrono::seconds endTime;
  int startImportance = 0;
  int endImportance = 100;
  float importance;
};
