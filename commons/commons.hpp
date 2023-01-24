#include <random>
#include <chrono>
#include <iostream>

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(0,65535); // guaranteed unbiased

// constexpr long long TEST_SIZE = 500'000'000;
constexpr long long TEST_SIZE = 500000;
constexpr long long REPEAT = 2;

template <typename Func>
void getExecutionTime(const std::string& title, Func func){                   // (4)

  std::chrono::duration<double> totalDur = std::chrono::duration<double>::zero();
    
  for(size_t i = 0; i < REPEAT; i++) {
    const auto sta = std::chrono::steady_clock::now();
    func();                                                                     // (5)
    const std::chrono::duration<double> dur = std::chrono::steady_clock::now() - sta;
    totalDur += dur;
  }

  std::cout << title << ": " << totalDur.count() << " sec. avarged over " << REPEAT << " runs." << std::endl;
}