#pragma once

#include "task.hpp"

#include <functional>
#include <vector>

struct GlobalState {
  std::vector<Task> tasksList;
  std::vector<Task> doneTasksList;

  using CmdMap = std::unordered_map<
      std::string_view,
      std::function<void(std::vector<std::string>, GlobalState &)>>;

  CmdMap cmdMap{};
};
