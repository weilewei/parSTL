
#include <commons.hpp>

void runTaskSize(const long long length) {

  std::vector<double> workVec(length);
  for (size_t i = 0; i < length; ++i) {
    workVec[i] = uni(rng);
  }

  getExecutionTime("nvc++ transform std::execution::seq", [workVec]() mutable {
    std::transform(std::execution::seq, workVec.begin(), workVec.end(),
                   workVec.begin(), [](double arg) { return std::tan(arg); });
  });

  getExecutionTime("nvc++ transform std::execution::par", [workVec]() mutable {
    std::transform(std::execution::par, workVec.begin(), workVec.end(),
                   workVec.begin(), [](double arg) { return std::tan(arg); });
  });

  getExecutionTime("nvc++ transform std::execution::par_unseq",
                   [workVec]() mutable {
                     std::transform(std::execution::par_unseq, workVec.begin(),
                                    workVec.end(), workVec.begin(),
                                    [](double arg) { return std::tan(arg); });
                   });

  getExecutionTime("nvc++ sort std::execution::seq", [workVec]() mutable {
    std::sort(std::execution::seq, workVec.begin(), workVec.end());
  });

  getExecutionTime("nvc++ sort std::execution::par", [workVec]() mutable {
    std::sort(std::execution::par, workVec.begin(), workVec.end());
  });

  getExecutionTime("nvc++ sort std::execution::par_unseq", [workVec]() mutable {
    std::sort(std::execution::par_unseq, workVec.begin(), workVec.end());
  });

  std::cout << '\n';
}

int main(int argc, char **argv) {
  long long length;

  char *a = argv[1];
  length = atoll(a);

  std::cout << "running experiment with size of " + std::to_string(length)
            << "\n";

  runTaskSize(length);
}