#include <commons.hpp>
#include <parallel/algorithm>

int main(){
  std::vector<double> workVec(TEST_SIZE);
  for (size_t i =0; i < TEST_SIZE; ++i) {
    workVec[i] = uni(rng);
  }
    
  getExecutionTime("__gnu_parallel::transform", [workVec]() mutable {                // (6)
    __gnu_parallel::transform(workVec.begin(), workVec.end(),        // (1)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }              
                  );
    });

  std::cout << '\n';
    
}