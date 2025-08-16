#pragma once

// #include "GlobalState.hpp"
#include <chrono>
#include <string>

class Task {
public:
  std::string name = "Default_name";
  bool localAdjustedTime = true;
  std::chrono::zoned_time<std::chrono::seconds, const std::chrono::time_zone *>
      startTime{std::chrono::current_zone(),
                floor<std::chrono::seconds>(std::chrono::system_clock::now())};
  std::chrono::zoned_time<std::chrono::seconds, const std::chrono::time_zone *>
      endTime{startTime.get_time_zone(),
              startTime.get_local_time() + std::chrono::days{1}};
  int startImportance = 0;
  int endImportance = 100;
  double importance = 0.f;
};

class TaskCategory {
  std::string name = "Default category name";
  std::vector<Task> tasksList;
};
