#include <commons.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>
#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>
    
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

  getExecutionTime("sort hpx::execution::seq", [workVec]() mutable {
    hpx::sort(hpx::execution::seq, workVec.begin(), workVec.end());
  });
         
  getExecutionTime("sort hpx ::execution::par", [workVec]() mutable { 
    hpx::sort(hpx::execution::par, workVec.begin(), workVec.end());        // (2)
  });
     
  getExecutionTime("sort hpx::execution::par_unseq", [workVec]() mutable {          // (8)
    hpx::sort(hpx::execution::par_unseq, workVec.begin(), workVec.end()); 
  });

  std::cout << '\n';
}