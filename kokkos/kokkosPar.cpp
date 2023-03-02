#include <commons.hpp>

#include<Kokkos_Core.hpp>
#include <Kokkos_Sort.hpp>

void runTaskSize(const long long length) {
  Kokkos::View<double*> workVec ("x", length);

  // Prevent touching workVec in serial so we don't mess up data affinity
  std::vector<double> workVecData(length);
  for (long long i = 0 ; i < length; ++i)
    workVecData[i] = uni(rng);

  Kokkos::parallel_for(length, KOKKOS_LAMBDA(const int& i) 
    { workVec(i) = workVecData[i]; });

  auto test = [=]() {
    Kokkos::parallel_for("kokkos::parallel_for transform optimized version", 
      Kokkos::RangePolicy<Kokkos::IndexType<int>, Kokkos::Schedule<Kokkos::Dynamic>>
      (0, length), KOKKOS_LAMBDA (const int& i) {
        workVec(i) = std::tan(workVec(i));
    });
  };

  test();
  getExecutionTime("kokkos::parallel_for transform optimized version", test);
}

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);

  long long length;

  char *a = argv[1];
  length = atoll(a);

  std::cout << "running experiment with size of " + std::to_string(length) << "\n";

  runTaskSize(length);

  Kokkos::finalize();
  std::cout << "\n";

}
    // {
    //   Kokkos::View<double*> workVec ("x", length);
   
    //   for (long long i = 0 ; i < length; ++i) 
    //     workVec(i) = uni(rng);

    //   getExecutionTime("kokkos::parallel_for transform", [&workVec]() mutable {                // (6)
    //     Kokkos::parallel_for("kokkos::parallel_for transform", length, KOKKOS_LAMBDA (const int& i) {
    //       workVec(i) = std::tan(workVec(i) );
    //     });
    //   });
    // }