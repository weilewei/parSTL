#include <commons.hpp>

    
int main(){

  std::vector<double> workVec(TEST_SIZE);
  for (size_t i =0; i < TEST_SIZE; ++i) {
    workVec[i] = uni(rng);
  }
    
  getExecutionTime("std::execution::seq", [workVec]() mutable {                // (6)
    std::transform(std::execution::seq, workVec.begin(), workVec.end(),        // (1)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }              
                  );
    });
        
  getExecutionTime("std::execution::par", [workVec]() mutable {                // (7)
    std::transform(std::execution::par, workVec.begin(), workVec.end(),        // (2)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });
     
  getExecutionTime("std::execution::par_unseq", [workVec]() mutable {          // (8)
    std::transform(std::execution::par_unseq, workVec.begin(), workVec.end(),  // (3)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });

  std::cout << '\n';
    
}