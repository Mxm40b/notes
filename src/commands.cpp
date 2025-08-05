#include "commands.hpp"

#include <chrono>
#include <print>
#include <stdexcept>

namespace cmds {
void help(std::vector<std::string> splitCommand, GlobalState &state) {
  std::println("This is the help message.\n"
               "To exit, try `exit`.\n"
               "To list commands, "
               "try `ls`.\n");
};

void exit(std::vector<std::string> splitCommand, GlobalState &state) {
  throw ExitCommand{};
}
void add(std::vector<std::string> splitCommand, GlobalState &state) {
  Task taskToAdd;
  for (size_t i = 1; i + 1 <= splitCommand.size(); i += 2) {
    if (i + 1 >= splitCommand.size()) {
      throw std::runtime_error("one argument incomplete: " + splitCommand[i]);
    }
    std::string arg = (splitCommand[i]);
    std::string argVal = (splitCommand[i + 1]);
    try {
      if (arg == "-s") {
        taskToAdd.startTime = std::chrono::seconds(std::stoi(argVal));
      } else if (arg == "-e") {
        taskToAdd.endTime = std::chrono::seconds(std::stoi(argVal));
      } else if (arg == "-si") {
        taskToAdd.startImportance = std::stoi(argVal);
      } else if (arg == "-ei") {
        taskToAdd.endImportance = std::stoi(argVal);
      } else if (arg == "-n") {
        taskToAdd.name = argVal;
      } else {
        throw std::runtime_error("invalid argument: " + arg);
      };
    } catch (const std::invalid_argument &e) {
      throw std::runtime_error("not a number: " + argVal);
    } catch (const std::out_of_range &e) {
      throw std::runtime_error("number too long: " + argVal);
    }
  }
  state.tasksList.emplace_back(taskToAdd);
  std::println(
      "Added task \nwith name: {}, \nwith startTime: {}, \nwith "
      "endTime:{}, \nwith startImportance:{}, \nwith endImportance:{}\n",
      taskToAdd.name, taskToAdd.startTime.count(), taskToAdd.endTime.count(),
      taskToAdd.startImportance, taskToAdd.endImportance);
}
void list(std::vector<std::string> splitCommand, GlobalState &state) {
  for (size_t i = 0; i < state.tasksList.size(); i++) {
    std::println(
        "Task {}: \nwith name: {}, \nwith startTime: {}, \nwith "
        "endTime: {}, \nwith startImportance: {}, \nwith endImportance: {},\n"
        "with importance: {}\n",
        i + 1, state.tasksList[i].name, state.tasksList[i].startTime.count(),
        state.tasksList[i].endTime.count(), state.tasksList[i].startImportance,
        state.tasksList[i].endImportance, state.tasksList[i].importance);
  }
};

void current(std::vector<std::string> splitCommand, GlobalState &state) {
  std::println("{}", std::chrono::duration_cast<std::chrono::seconds>(
                         std::chrono::system_clock::now().time_since_epoch()));
};

} // namespace cmds
