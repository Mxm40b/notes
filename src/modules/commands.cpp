#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "tasks.cpp"

void print(std::string text, bool newLine = true) {
  if (newLine) {
    std::cout << text << std::endl;
  } else {
    std::cout << text;
  }
}

void help(std::vector<std::string> splitCommand, std::vector<Task> &tasksList) {
  print("This is the help message.\n"
        "To exit, try `exit`.\n"
        "To list commands, "
        "try `ls`.\n"
        "To add a command, try `add`.");
};

void add(std::vector<std::string> splitCommand, std::vector<Task> &tasksList) {}
