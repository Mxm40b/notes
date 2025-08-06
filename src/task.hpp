#pragma once

// #include "GlobalState.hpp"
#include <chrono>
#include <string>

class Task {
public:
  std::string name = "Default_name";
  std::chrono::seconds startTime =
      std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch());
  std::chrono::seconds endTime = startTime + std::chrono::seconds(100);
  int startImportance = 0;
  int endImportance = 100;
  double importance = 0.f;
};

class TaskCategory {
  std::string name = "Default category name";
  std::vector<Task> tasksList;
};
