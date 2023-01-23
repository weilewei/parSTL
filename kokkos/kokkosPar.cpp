#include<Kokkos_Core.hpp>
#include<cstdio>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// constexpr long long size = 500'000'000;  
constexpr long long size = 80; 
const double pi = std::acos(-1);

template <typename Func>
void getExecutionTime(const std::string& title, Func func){                   // (4)
    
  const auto sta = std::chrono::steady_clock::now();
  func();                                                                     // (5)
  const std::chrono::duration<double> dur = std::chrono::steady_clock::now() - sta;
  std::cout << title << ": " << dur.count() << " sec. " << std::endl;
     
}

int main(int argc, char* argv[]) {
    Kokkos::initialize(argc,argv);

    {
      Kokkos::View<double*> x ("x", size);
   
      std::mt19937 engine;
      std::uniform_real_distribution<> uniformDist(0, pi / 2);
      for (long long i = 0 ; i < size ; ++i) 
        x(i) = uniformDist(engine);

      getExecutionTime("kokkos::parallel_for transform", [&x]() mutable {                // (6)
        Kokkos::parallel_for("kokkos::parallel_for transform", size, KOKKOS_LAMBDA (const int& i) {
          x(i) = std::tan(i);
        });
      });
    }
    Kokkos::finalize();
}