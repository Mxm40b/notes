#pragma once

#include "task.hpp"
#include <chrono>

#include <functional>
#include <vector>

struct taskArgPair {
  std::string arg = "";
  std::string argValue = "";
};

struct GlobalState {
  std::chrono::zoned_time<std::chrono::seconds, const std::chrono::time_zone *>
      currentTime{
          std::chrono::current_zone(),
          floor<std::chrono::seconds>(std::chrono::system_clock::now())};
  std::vector<TaskCategory> CategoriesList;
  std::vector<Task> tasksList;
  std::vector<Task> doneTasksList;

  using CmdMap = std::unordered_map<
      std::string_view,
      std::function<void(std::vector<taskArgPair>, GlobalState &)>>;

  CmdMap cmdMap{};
};
