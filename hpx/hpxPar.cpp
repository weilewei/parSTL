#include <commons.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>
#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <cmath>
#include <execution>
#include <iostream>
#include <string>
#include <vector>
    
int main(){
  std::vector<double> workVec(TEST_SIZE);
  for (size_t i =0; i < TEST_SIZE; ++i) {
    workVec[i] = uni(rng);
  }
    
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