#include "commands.hpp"

#include <print>

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
} // namespace cmds
