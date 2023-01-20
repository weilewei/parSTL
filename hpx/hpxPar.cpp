// parallelSTLPerformance.cpp

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>
#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

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
    
int main(){

  std::cout << '\n';
    
  std::vector<double> randValues;
  randValues.reserve(size);
   
  std::mt19937 engine;
  std::uniform_real_distribution<> uniformDist(0, pi / 2);
  for (long long i = 0 ; i < size ; ++i) randValues.push_back(uniformDist(engine));
    
  std::vector<double> workVec(randValues);
    
  getExecutionTime("hpx::execution::seq", [workVec]() mutable {                // (6)
    hpx::transform(hpx::execution::seq, workVec.begin(), workVec.end(),        // (1)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }              
                  );
    });
        
  getExecutionTime("hpx::execution::par", [workVec]() mutable {                // (7)
    hpx::transform(hpx::execution::par, workVec.begin(), workVec.end(),        // (2)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });
     
  getExecutionTime("hpx::execution::par_unseq", [workVec]() mutable {          // (8)
    hpx::transform(hpx::execution::par_unseq, workVec.begin(), workVec.end(),  // (3)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });

  std::cout << '\n';
    
}