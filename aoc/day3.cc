#include <stddef.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace aoc {

class Day3 {
 public:
  Day3() = delete;

  Day3(const Day3&) = delete;
  Day3& operator=(const Day3&) = delete;

  static size_t SolvePart1();
  static size_t SolvePart2();

 private:
  static constexpr size_t kNumBits = 12;

  static std::vector<std::bitset<kNumBits>> ParseBinaryNums();
  static std::array<size_t, 2> CountBits(
      const std::vector<std::bitset<kNumBits>>& nums, size_t pos);
};

}  // namespace aoc

size_t aoc::Day3::SolvePart1() {
  auto nums = Day3::ParseBinaryNums();
  std::bitset<Day3::kNumBits> gamma_rate = 0;
  std::bitset<Day3::kNumBits> epsilon_rate = 0;

  for (size_t i = Day3::kNumBits - 1; i < Day3::kNumBits; --i) {
    auto num_bits = Day3::CountBits(nums, i);
    int mcb = num_bits.at(0) >= nums.size() - num_bits.at(0) ? 0 : 1;
    gamma_rate[i] = mcb;
    epsilon_rate[i] = !mcb;
  }

  return gamma_rate.to_ullong() * epsilon_rate.to_ullong();
}

size_t aoc::Day3::SolvePart2() {
  auto nums = Day3::ParseBinaryNums();
  std::vector<std::bitset<kNumBits>> o2_nums(nums);
  std::vector<std::bitset<kNumBits>> co2_nums(nums);

  for (size_t i = Day3::kNumBits - 1; i < Day3::kNumBits; --i) {
    auto o2_num_bits = Day3::CountBits(o2_nums, i);
    auto co2_num_bits = Day3::CountBits(co2_nums, i);
    int mcb = o2_num_bits[1] >= o2_nums.size() - o2_num_bits[1] ? 1 : 0;
    int lcb = co2_num_bits[0] <= co2_nums.size() - co2_num_bits[0] ? 0 : 1;

    // std::cout << "Position: " << i << '\n';
    // std::cout << "MCB (O2): " << mcb << '\n';
    // std::cout << "LCB (CO2): " << lcb << '\n';
    // for (const auto& n : o2_nums) {
    //   std::cout << n.to_string() << '\n';
    // }

    for (auto it = o2_nums.begin(); it != o2_nums.end();) {
      if (o2_nums.size() == 1) {
        break;
      }

      if ((*it)[i] != mcb) {
        it = o2_nums.erase(it);
      } else {
        ++it;
      }
    }

    for (auto it = co2_nums.begin(); it != co2_nums.end();) {
      if (co2_nums.size() == 1) {
        break;
      }

      if ((*it)[i] != lcb) {
        it = co2_nums.erase(it);
      } else {
        ++it;
      }
    }
  }

  return o2_nums.front().to_ullong() * co2_nums.front().to_ullong();
}

std::vector<std::bitset<aoc::Day3::kNumBits>> aoc::Day3::ParseBinaryNums() {
  std::vector<std::bitset<Day3::kNumBits>> nums;
  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      break;
    }

    nums.emplace_back(line);
  }

  return nums;
}

std::array<size_t, 2> aoc::Day3::CountBits(
    const std::vector<std::bitset<aoc::Day3::kNumBits>>& nums, size_t pos) {
  std::array<size_t, 2> num_bits{0, 0};
  for (const auto& num : nums) {
    if (num[pos] == 0) {
      ++num_bits[0];
    } else if (num[pos] == 1) {
      ++num_bits[1];
    } else {
      std::cerr << "Unkown bit value '" << num[pos]
                << "' detected at position '" << pos << "'!\n";
    }
  }

  return num_bits;
}

int main(int, const char*[]) {
  std::cout << aoc::Day3::SolvePart2() << '\n';
  return 0;
}