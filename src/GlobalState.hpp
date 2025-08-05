#pragma once

#include "task.hpp"
#include <chrono>

#include <functional>
#include <vector>

struct GlobalState {
  std::chrono::sys_time<std::chrono::seconds> currentTime =
      floor<std::chrono::seconds>(std::chrono::system_clock::now());
  ;
  std::chrono::local_time<std::chrono::seconds> localTime =
      std::chrono::zoned_time{std::chrono::current_zone(), currentTime}
          .get_local_time();
  std::vector<Task> tasksList;
  std::vector<Task> doneTasksList;

  using CmdMap = std::unordered_map<
      std::string_view,
      std::function<void(std::vector<std::string>, GlobalState &)>>;

  CmdMap cmdMap{};
};
