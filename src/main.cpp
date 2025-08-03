#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <vector>

using Func = std::function<void()>;
using CommandDictionary = std::vector<std::pair<std::string, Func>>;

class Task {
public:
  std::string name;
  std::chrono::seconds startTime;
  std::chrono::seconds endTime;
  int startImportance = 0;
  int endImportance = 100;
  double importance;
};

std::vector<Task> tasksList;

std::vector<Task> doneTasksList;

void print(std::string text, bool newLine = true) {
  if (newLine) {
    std::cout << text << std::endl;
  } else {
    std::cout << text;
  }
}

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
      commandDictionary[i].second();
      return 0;
    }
  };
  return 1;
};

void help() { print("This is the help message."); };

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
  using Func = std::function<void()>;
  using CommandDictionary = std::vector<std::pair<std::string, Func>>;
  CommandDictionary commandDictionary;
  commandDictionary.push_back(
      {"fuck-you", []() { print("uno reverse card"); }});
  commandDictionary.emplace_back("help", []() { help(); });

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
