#include <commons.hpp>
#include <parallel/algorithm>

void runTaskSize(const long long length) {
  std::vector<double> workVec(length);
  for (size_t i =0; i < length; ++i) {
    workVec[i] = uni(rng);
  }
    
  getExecutionTime("__gnu_parallel::transform", [workVec]() mutable {                // (6)
    __gnu_parallel::transform(workVec.begin(), workVec.end(),        // (1)
		   workVec.begin(), 
                   [](double arg){ return std::tan(arg); }              
                  );
    });
    
  getExecutionTime("__gnu_parallel::sort", [workVec]() mutable {                // (6)
    __gnu_parallel::sort(workVec.begin(), workVec.end());});

  std::cout << '\n';
}


int main(int argc, char** argv){
  long long length;

  char *a = argv[1];
  length = atoll(a);

  std::cout << "running experiment with size of " + std::to_string(length) << "\n";

  runTaskSize(length);
}