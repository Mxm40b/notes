#include "commands.hpp"
#include "GlobalState.hpp"

#include <chrono>
#include <exception>
#include <format>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace cmds {
std::string formatTime(std::chrono::local_time<std::chrono::seconds> time) {
  return std::format("{:%d/%m at %H:%M:%S}", time);
}
std::string formatTime(std::chrono::year_month_day ymd) {
  return std::to_string(unsigned(ymd.day())) + "/" +
         std::to_string(unsigned(ymd.month())) + "/" +
         std::to_string(int(ymd.year()));
}
std::string formatTime(std::chrono::seconds time) {
  std::chrono::sys_time<std::chrono::seconds> sysTime{time};
  std::chrono::zoned_time<std::chrono::seconds> zonedTime{sysTime};
  return formatTime(zonedTime.get_local_time());
}
std::chrono::year intToYear(int year_int) {
  if (year_int < 0 || year_int > 99) {
    throw std::runtime_error("invalid year: " + std::to_string(year_int) +
                             "; must be between 20[00] and 20[99]");
  };
  return std::chrono::year{2000 + year_int};
}

std::chrono::year_month_day
getCalendarDate(std::chrono::sys_time<std::chrono::seconds> time) {
  std::chrono::sys_days currentDay = floor<std::chrono::days>(time);
  std::chrono::year_month_day ymd{currentDay};
  return ymd;
};

bool isValidDate(std::chrono::year year, int month_int, int day_int) {
  std::chrono::month month{unsigned(month_int)};
  std::chrono::day day{unsigned(day_int)};
  if (!month.ok() || !day.ok()) {
    return false;
  }
  std::chrono::year_month_day ymd{year, month, day};
  return ymd.ok();
}

std::chrono::year_month_day readDate(std::string date, GlobalState &state) {
  char sep;
  int day_int;
  int month_int;
  int year_int;

  std::istringstream ss(date);

  if (ss >> day_int >> sep >> month_int && sep == '/') {
    if (cmds::isValidDate(cmds::getCalendarDate(state.currentTime).year(),
                          month_int, day_int)) {
      return std::chrono::year_month_day{
          cmds::getCalendarDate(state.currentTime).year(),
          std::chrono::month{unsigned(month_int)},
          std::chrono::day{unsigned(day_int)}};
    }
  }
  if (ss >> day_int >> sep >> month_int >> sep >> year_int && sep == '/') {
    if (cmds::isValidDate(cmds::intToYear(year_int), month_int, day_int)) {
      return std::chrono::year_month_day{
          cmds::intToYear(year_int), std::chrono::month{unsigned(month_int)},
          std::chrono::day{unsigned(day_int)}};
    }
  }
  throw std::runtime_error("invalid date: " + date);
};

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
      taskToAdd.name, formatTime(taskToAdd.startTime),
      formatTime(taskToAdd.endTime), taskToAdd.startImportance,
      taskToAdd.endImportance);
}

void list(std::vector<std::string> splitCommand, GlobalState &state) {
  for (size_t i = 0; i < state.tasksList.size(); i++) {
    std::println("Task {}: \nwith name: {}, \nwith startTime: {}, \nwith "
                 "endTime: {}, \nwith startImportance: {}, \nwith "
                 "endImportance: {},\n"
                 "with importance: {}\n",
                 i + 1, state.tasksList[i].name,
                 formatTime(state.tasksList[i].startTime),
                 formatTime(state.tasksList[i].endTime),
                 state.tasksList[i].startImportance,
                 state.tasksList[i].endImportance,
                 state.tasksList[i].importance);
  }
};

void current(std::vector<std::string> splitCommand, GlobalState &state) {
  // std::println("{}", std::chrono::duration_cast<std::chrono::seconds>(
  // std::chrono::system_clock::now().time_since_epoch()));
  std::string formattedTime =
      std::format("{:%d/%m at %H:%M:%S}", state.localTime);
  std::println("{}", formatTime(state.localTime));
};

} // namespace cmds
