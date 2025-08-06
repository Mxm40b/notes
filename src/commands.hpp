#pragma once

#include "GlobalState.hpp"

#include <string>
#include <vector>

namespace cmds {
void help(std::vector<std::string> splitCommand, GlobalState &state);
struct ExitCommand : public std::exception {
  const char *what() const noexcept override { return "Exit command issued"; }
};

void exit(std::vector<std::string> splitCommand, GlobalState &state);

void add(std::vector<std::string> splitCommand, GlobalState &state);

void edit(std::vector<std::string> splitCommand, GlobalState &state);

void list(std::vector<std::string> splitCommand, GlobalState &state);

void current(std::vector<std::string> splitCommand, GlobalState &state);
} // namespace cmds
