#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "modules/commands.cpp"

using Func = std::function<void(std::vector<std::string>, std::vector<Task>)>;
using CommandDictionary = std::vector<std::pair<std::string, Func>>;

std::vector<Task> tasksList;

std::vector<Task> doneTasksList;

int executeCommand(std::vector<std::string> splitCommand,
                   CommandDictionary commandDictionary) {
  if (splitCommand[0] == "") {
    return 2;
  }
  if (splitCommand[0] == "exit") {
    return -1;
  }
  for (int i = 0; i < commandDictionary.size(); i++) {
    if (commandDictionary[i].first == splitCommand[0]) {
      commandDictionary[i].second(splitCommand, &tasksList);
      return 0;
    }
  };
  return 1;
};

int prompt(CommandDictionary commandDictionary) {
  std::string command;
  print("> ", 0);
  std::cin >> command;

  std::istringstream iss(command);

  std::string word;
  std::vector<std::string> splitCommand;

  while (iss >> word) {
    splitCommand.push_back(word);
  }

  return executeCommand(splitCommand, commandDictionary);
}

int err;

int main() {
  using Func = std::function<void(std::vector<std::string>, std::vector<Task>)>;
  using CommandDictionary = std::vector<std::pair<std::string, Func>>;
  CommandDictionary commandDictionary;
  // commandDictionary.push_back(
  //     {"fuck-you", [](std::vector<std::string>, std::vector<Task> &tasksList)
  //     {
  //        print("uno reverse card");
  //      }});
  commandDictionary.emplace_back(
      "help", [](std::vector<std::string> args, std::vector<Task> &tasksList) {
        help(args, tasksList);
      });
  commandDictionary.emplace_back(
      "add", [](std::vector<std::string> args, std::vector<Task> &tasksList) {
        add(args, tasksList);
      });

  print("Hello, you are using Notes. To learn how to use it, try `help`");
  bool Quit = false;
  while (!Quit) {
    err = prompt(commandDictionary);
    switch (err) {
    case -1:
      Quit = true;
      break;
    case 1:
      print("Command not found");
      break;
    case 2:
      print("No command inserted");
      break;
    default:
      break;
    }
  }
  return 0;
}
