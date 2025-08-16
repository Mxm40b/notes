#pragma once

#include "GlobalState.hpp"

#include <string>
#include <vector>

namespace cmds {

std::vector<taskArgPair> argsVector(std::vector<std::string> splitCommand);
void help(std::vector<taskArgPair> args, GlobalState &state);
struct ExitCommand : public std::exception {
  const char *what() const noexcept override { return "Exit command issued"; }
};

void exit(std::vector<taskArgPair> args, GlobalState &state);

void add(std::vector<taskArgPair> args, GlobalState &state);

void edit(std::vector<taskArgPair> args, GlobalState &state);

void list(std::vector<taskArgPair> args, GlobalState &state);

void current(std::vector<taskArgPair> args, GlobalState &state);
} // namespace cmds
