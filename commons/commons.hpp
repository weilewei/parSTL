#include <chrono>
#include <iostream>
#include <random>

#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <string>
#include <vector>

std::random_device rd; // only used once to initialise (seed) engine
std::mt19937
    rng(rd()); // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(0, 65535); // guaranteed unbiased

// default repeatition time is 5
constexpr long long REPEAT = 5;

template <typename Func>
void getExecutionTime(const std::string &title, Func func) {

  std::chrono::duration<double> totalDur =
      std::chrono::duration<double>::zero();

  for (size_t i = 0; i < REPEAT; i++) {
    const auto sta = std::chrono::steady_clock::now();
    func();
    const std::chrono::duration<double> dur =
        std::chrono::steady_clock::now() - sta;
    totalDur += dur;
  }

  std::cout << title << ": " << totalDur.count() / REPEAT
            << " sec. averaged over " << REPEAT << " runs." << std::endl;
}