#include <stddef.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace aoc {

class Day2 {
 public:
  Day2() = delete;

  Day2(const Day2&) = delete;
  Day2& operator=(const Day2&) = delete;

  static size_t SolvePart1();
  static size_t SolvePart2();

 private:
  enum Direction {
    kForwardDirection,
    kDownDirection,
    kUpDirection,
    kNumDirections
  };

  struct Command {
    Command(const Direction& direction, size_t units)
        : direction(direction), units(units) {}

    Command(const Command&) = default;
    Command& operator=(const Command&) = default;

    Direction direction;
    size_t units;
  };

  static constexpr std::string_view kForwardDirectionName = "forward";
  static constexpr std::string_view kDownDirectionName = "down";
  static constexpr std::string_view kUpDirectionName = "up";

  static std::vector<Command> ParseCommands();
  static std::optional<Direction> DirectionOf(std::string_view name);
};

}  // namespace aoc

size_t aoc::Day2::SolvePart1() {
  auto commands = Day2::ParseCommands();
  size_t horizontal_pos = 0;
  size_t depth = 0;

  std::for_each(commands.begin(), commands.end(), [&](const Command& command) {
    if (command.direction == kForwardDirection) {
      horizontal_pos += command.units;
    } else if (command.direction == kDownDirection) {
      depth += command.units;
    } else if (command.direction == kUpDirection) {
      depth -= command.units;
    }
  });

  return horizontal_pos * depth;
}

size_t aoc::Day2::SolvePart2() {
  auto commands = Day2::ParseCommands();
  size_t horizontal_pos = 0;
  size_t depth = 0;
  size_t aim = 0;

  std::for_each(commands.begin(), commands.end(), [&](const Command& command) {
    if (command.direction == kForwardDirection) {
      horizontal_pos += command.units;
      depth += aim * command.units;
    } else if (command.direction == kDownDirection) {
      aim += command.units;
    } else if (command.direction == kUpDirection) {
      aim -= command.units;
    }
  });

  return horizontal_pos * depth;
}

std::vector<aoc::Day2::Command> aoc::Day2::ParseCommands() {
  std::vector<Command> commands;
  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      break;
    }

    size_t delimeter = line.find(" ");
    std::string direction_name = line.substr(0, delimeter);
    auto direction = Day2::DirectionOf(direction_name);
    size_t units = std::stoll(line.substr(delimeter, line.size()));

    if (direction) {
      commands.emplace_back(*direction, units);
    }
  }

  return commands;
}

std::optional<aoc::Day2::Direction> aoc::Day2::DirectionOf(
    std::string_view name) {
  if (name == kForwardDirectionName) {
    return std::make_optional<Direction>(kForwardDirection);
  } else if (name == kDownDirectionName) {
    return std::make_optional<Direction>(kDownDirection);
  } else if (name == kUpDirectionName) {
    return std::make_optional<Direction>(kUpDirection);
  } else {
    return std::nullopt;
  }
}

int main(int, const char*[]) {
  std::cout << aoc::Day2::SolvePart2() << '\n';
  return 0;
}