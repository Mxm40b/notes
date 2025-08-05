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
#include "task.hpp"

void updateImportance(GlobalState &state) {
  state.currentTime = std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now().time_since_epoch());
  for (size_t i = 0; i + 1 <= state.tasksList.size(); i++) {
    if (!state.tasksList.empty() ||
        (state.tasksList[i].endTime - state.tasksList[i].startTime).count() !=
            0) {
      long double slope =
          (state.tasksList[i].endImportance -
           state.tasksList[i].startImportance) /
          (state.tasksList[i].endTime - state.tasksList[i].startTime).count();
      state.tasksList[i].importance =
          slope * state.currentTime.count() +
          slope * state.tasksList[i].startTime.count() -
          state.tasksList[i].startImportance;
    }
  }
};

void executeCommand(std::vector<std::string> splitCommand, GlobalState &state) {
  if (!state.cmdMap.contains(splitCommand[0]))
    throw std::runtime_error(
        std::format("Couldnt find command {}", splitCommand[0]));
  state.cmdMap[splitCommand[0]](splitCommand, state);
};

void prompt(GlobalState &state) {
  std::string commandLine;
  std::print("> ");
  std::getline(std::cin, commandLine);

  std::istringstream iss(commandLine);

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
  state.tasksList.emplace_back();
  auto &cmdMap = state.cmdMap;
  cmdMap["help"] = cmds::help;
  cmdMap["exit"] = cmds::exit;
  cmdMap["add"] = cmds::add;
  cmdMap["list"] = cmds::list;
  cmdMap["current"] = cmds::current;

  std::println(
      "Hello, you are using Notes. To learn how to use it, try `help`\n");
  while (true) {
    updateImportance(state);
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
