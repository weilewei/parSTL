#include <commons.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>
#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>
    
void runTaskSize(const long long length){
  std::vector<double> workVec(length);
  for (size_t i =0; i < length; ++i) {
    workVec[i] = uni(rng);
  }
    
  getExecutionTime("transform hpx::execution::seq", [workVec]() mutable {
    hpx::transform(hpx::execution::seq, workVec.begin(), workVec.end(),
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }              
                  );
    });
        
  getExecutionTime("transform hpx::execution::par", [workVec]() mutable {
    hpx::transform(hpx::execution::par, workVec.begin(), workVec.end(),
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });
     
  getExecutionTime("transform hpx::execution::par_unseq", [workVec]() mutable {
    hpx::transform(hpx::execution::par_unseq, workVec.begin(), workVec.end(),
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }
                  );
  });

  getExecutionTime("sort hpx::execution::seq", [workVec]() mutable {
    hpx::sort(hpx::execution::seq, workVec.begin(), workVec.end());
  });
         
  getExecutionTime("sort hpx ::execution::par", [workVec]() mutable { 
    hpx::sort(hpx::execution::par, workVec.begin(), workVec.end());
  });
     
  getExecutionTime("sort hpx::execution::par_unseq", [workVec]() mutable {
    hpx::sort(hpx::execution::par_unseq, workVec.begin(), workVec.end()); 
  });

  std::cout << '\n';
}

int main(int argc, char** argv){
  long long length;

  char *a = argv[1];
  length = atoll(a);

  std::cout << "running experiment with size of " + std::to_string(length) << "\n";

  runTaskSize(length);
}