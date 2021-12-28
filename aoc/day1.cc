#include <stddef.h>

#include <iostream>
#include <string>
#include <vector>

namespace aoc {

class Day1 {
 public:
  Day1() = delete;

  Day1(const Day1&) = delete;
  Day1& operator=(const Day1&) = delete;

  static size_t SolvePart1();
  static size_t SolvePart2();

 private:
  static std::vector<size_t> ParseDepths();
};

}  // namespace aoc

size_t aoc::Day1::SolvePart1() {
  auto depths = Day1::ParseDepths();
  size_t num_increases = 0;

  for (size_t i = 1, n = depths.size(); i < n; ++i) {
    if (depths[i] > depths[i - 1]) {
      ++num_increases;
    }
  }

  return num_increases;
}

size_t aoc::Day1::SolvePart2() {
  auto depths = Day1::ParseDepths();
  if (depths.size() < 6) {
    return 0;
  }

  size_t prev_sum = 0;
  size_t num_increases = 0;

  for (size_t i = 0, n = depths.size(); i + 2 < n; ++i) {
    size_t sum = depths[i] + depths[i + 1] + depths[i + 2];

    if (i != 0 && sum > prev_sum) {
      ++num_increases;
    }

    prev_sum = sum;
  }

  return num_increases;
}

std::vector<size_t> aoc::Day1::ParseDepths() {
  std::vector<size_t> depths;
  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      break;
    }

    depths.push_back(std::stoull(line));
  }

  return depths;
}

int main(int, const char*[]) {
  std::cout << aoc::Day1::SolvePart2() << '\n';
  return 0;
}
