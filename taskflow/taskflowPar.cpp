#include <commons.hpp>
#include <taskflow.hpp>
#include <algorithm/sort.hpp>

int main(int argc, char** argv){

  long long length;
  char *a = argv[1];
  length = atoll(a);

  int num_threads;
  char *b = argv[2];
  num_threads = atoi(b);

  std::cout << "running experiment with size of " + std::to_string(length) << "\n";
  std::cout << "running with number of threads: " << num_threads << "\n";

  tf::Executor executor(num_threads);

  std::vector<double> workVec(length);
  for (size_t i =0; i < length; ++i) {
    workVec[i] = uni(rng);
  }

  tf::Taskflow t1;
  t1.for_each(workVec.begin(), workVec.end(), [] (double arg) {
    arg = std::tan(arg);
  });
    
  getExecutionTime("taskflow transform", [&]() mutable {
    executor.run(t1).wait();
  });

  tf::Taskflow t2;
  t2.sort(workVec.begin(), workVec.end());

  getExecutionTime("taskflow sort", [&]() mutable {              
    executor.run(t2).wait();
  });
        
  std::cout << '\n';
}