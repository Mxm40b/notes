#include <csignal>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

#include "GlobalState.hpp"
#include "commands.hpp"

void executeCommand(std::vector<std::string> splitCommand, GlobalState &state) {
  if (!state.cmdMap.contains(splitCommand[0]))
    throw std::runtime_error(
        std::format("Couldnt find command {}", splitCommand[0]));
  state.cmdMap[splitCommand[0]](splitCommand, state);
};

void prompt(GlobalState &state) {
  std::string command;
  std::print("> ");
  std::cin >> command;

  std::istringstream iss(command);

  std::string word;
  std::vector<std::string> splitCommand;

  while (iss >> word) {
    splitCommand.push_back(word);
  }

  executeCommand(splitCommand, state);
}

void handleInterrupt(int signal) {
  std::println("Quitting.");
  exit(EXIT_SUCCESS);
}

int main() {
  std::signal(SIGINT, handleInterrupt);

  GlobalState state{};
  auto &cmdMap = state.cmdMap;
  cmdMap["help"] = cmds::help;
  cmdMap["exit"] = cmds::exit;

  std::println(
      "Hello, you are using Notes. To learn how to use it, try `help`");
  bool Quit = false;
  while (!Quit) {
    try {
      prompt(state);
    } catch (const cmds::ExitCommand &) {
      std::println("Quitting.");
      break; // Exit the loop on exit command
    } catch (const std::runtime_error &e) {
      std::println("{}", e.what()); // Handle actual errors
    }
  }
  return 0;
}
