#include "commands.hpp"
#include "GlobalState.hpp"

#include <algorithm>
#include <chrono>
#include <exception>
#include <format>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace cmds {

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

void help(std::vector<std::string> splitCommand, GlobalState &state) {
  std::println("This is the help message.\n"
               "To exit, try `exit`.\n"
               "To list commands, "
               "try `ls`.\n");
};

void exit(std::vector<std::string> splitCommand, GlobalState &state) {
  throw ExitCommand{};
}

void list(std::vector<std::string> splitCommand, GlobalState &state) {
  for (size_t i = 0; i < state.tasksList.size(); i++) {
    std::println("Task number: {}", i);
    showTask(state.tasksList[i]);
  }
};

void editTask(std::vector<std::string> splitArgs, Task &task) {}

void add(std::vector<std::string> splitCommand, GlobalState &state) {
  Task newTask;
  splitCommand.erase(splitCommand.begin());
  editTask(splitCommand, newTask);
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

void edit(std::vector<std::string> splitCommand, GlobalState &state) {
  splitCommand.erase(splitCommand.begin());
  Task &taskToEdit = findTask(splitCommand[0], state);
  splitCommand.erase(splitCommand.begin());
  editTask(splitCommand, taskToEdit);
}

void remove(std::vector<std::string> splitCommand, GlobalState &state) {}
void complete(std::vector<std::string> splitCommand, GlobalState &state) {}

void current(std::vector<std::string> splitCommand, GlobalState &state) {
  std::println("{}", formatTime(state.currentTime));
};

} // namespace cmds
