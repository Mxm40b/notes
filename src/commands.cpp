#include "commands.hpp"
#include "GlobalState.hpp"

#include <algorithm>
#include <chrono>
#include <exception>
#include <format>
#include <istream>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace cmds {

std::vector<taskArgPair> argsVector(std::vector<std::string> splitCommand) {
  std::vector<taskArgPair> argsVector;
  while (!splitCommand.empty()) {
    if (splitCommand[0][0] != '-') {
      argsVector.push_back(taskArgPair{.argValue = splitCommand[0]});
      splitCommand.erase(splitCommand.begin());
    } else if (splitCommand.size() >= 2) {
      if (splitCommand[1][0] != '-') {
        argsVector.push_back(
            taskArgPair{.arg = splitCommand[0], .argValue = splitCommand[1]});
        splitCommand.erase(splitCommand.begin());
        splitCommand.erase(splitCommand.begin());
      }
    } else {
      argsVector.push_back(taskArgPair{.arg = splitCommand[0]});
      splitCommand.erase(splitCommand.begin());
    }
  }
  return argsVector;
}

Task &findTask(std::string name, GlobalState &state) {
  auto findByName =
      std::find_if(state.tasksList.begin(), state.tasksList.end(),
                   [&](const Task &task) { return (task.name == name); });
  if (findByName == state.tasksList.end()) {
    throw std::runtime_error("Task not found");
  }
  Task &task = *findByName;
  return task;
}

std::string formatTime(std::chrono::zoned_time<std::chrono::seconds,
                                               const std::chrono::time_zone *>
                           time) {
  return std::format("{:%d/%m at %H:%M:%S}", time.get_local_time());
}
void showTask(Task &task) {
  std::println("\nwith name: {}, \nwith startTime: {}, \nwith "
               "endTime: {}, \nwith startImportance: {}, \nwith "
               "endImportance: {},\n"
               "with importance: {}\n",
               task.name, formatTime(task.startTime), formatTime(task.endTime),
               task.startImportance, task.endImportance, task.importance);
}
std::chrono::year intToYear(int year_int) {
  if (year_int < 0 || year_int > 99) {
    throw std::runtime_error("invalid year: " + std::to_string(year_int) +
                             "; must be between 20[00] and 20[99]");
  };
  return std::chrono::year{2000 + year_int};
}

bool isValidDate(std::chrono::year year, int month_int, int day_int) {
  std::chrono::month month{unsigned(month_int)};
  std::chrono::day day{unsigned(day_int)};
  if (!month.ok() || !day.ok()) {
    return false;
  }
  std::chrono::year_month_day ymd{year, month, day};
  return ymd.ok();
}

void help(std::vector<taskArgPair> args, GlobalState &state) {
  std::println(
      "This is the help message.\n"
      "To exit, try `exit`.\n"
      "To list tasks, "
      "try `ls`.\n"
      "to add a task, use `add [parameters: -n for name, -si for start "
      "importance, \n-ei for end importance, -st for start time, -et for end "
      "time, \n-sd for start date, -ed for end date]`\n"
      "to edit a task, use `edit [task name] [parameters: -n for name, \n-si "
      "for "
      "start importance, -ei for end importance, -st for start time, \n-et for "
      "end time, -sd for start date, -ed for end date]`");
};

void exit(std::vector<taskArgPair> args, GlobalState &state) {
  throw ExitCommand{};
}

void list(std::vector<taskArgPair> args, GlobalState &state) {
  for (size_t i = 0; i < state.tasksList.size(); i++) {
    std::println("Task number: {}", i);
    showTask(state.tasksList[i]);
  }
};

void editTask(std::vector<taskArgPair> args, Task &task) {}

void add(std::vector<taskArgPair> args, GlobalState &state) {
  Task newTask;
  editTask(args, newTask);
  try {
    findTask(newTask.name, state);
  } catch (const std::runtime_error &e) {
    if (e.what() == "Task not found") {
      state.tasksList.push_back(newTask);
      return;
    } else {
      throw e;
    }
  };
  throw std::runtime_error("Task already exists");
}

void edit(std::vector<taskArgPair> args, GlobalState &state) {
  if (args[0].arg[0] == '-') {
    throw std::runtime_error("First argument must be the name of the task to "
                             "edit, not a parameter. \nsee `help` for further "
                             "information on usage.");
  }
  Task &taskToEdit = findTask(args[0].argValue, state);
  args.erase(args.begin());
  editTask(args, taskToEdit);
}

void remove(std::vector<taskArgPair> splitCommand, GlobalState &state) {}
void complete(std::vector<taskArgPair> splitCommand, GlobalState &state) {}

void current(std::vector<taskArgPair> splitCommand, GlobalState &state) {
  std::println("{}", formatTime(state.currentTime));
};

} // namespace cmds
