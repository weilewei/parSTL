#include <commons.hpp>

#include<Kokkos_Core.hpp>

int main(int argc, char* argv[]) {
    Kokkos::initialize(argc,argv);

    {
      Kokkos::View<double*> workVec ("x", TEST_SIZE);
   
      for (long long i = 0 ; i < TEST_SIZE; ++i) 
        workVec(i) = uni(rng);

      getExecutionTime("kokkos::parallel_for transform", [&workVec]() mutable {                // (6)
        Kokkos::parallel_for("kokkos::parallel_for transform", TEST_SIZE, KOKKOS_LAMBDA (const int& i) {
          workVec(i) = std::tan(workVec(i) );
        });
      });
    }

    {
      Kokkos::View<double*> workVec ("x", TEST_SIZE);

      // Prevent touching workVec in serial so we don't mess up data affinity
      std::vector<double> workVecData(TEST_SIZE);
      for (long long i = 0 ; i < TEST_SIZE; ++i)
        workVecData[i] = uni(rng);

      Kokkos::parallel_for(TEST_SIZE, KOKKOS_LAMBDA(const int& i) { workVec(i) = workVecData[i]; });

      auto test = [=]() {
        Kokkos::parallel_for("kokkos::parallel_for transform optimized version", Kokkos::RangePolicy<Kokkos::IndexType<int>, Kokkos::Schedule<Kokkos::Dynamic>>(0, TEST_SIZE), KOKKOS_LAMBDA (const int& i) {
          workVec(i) = std::tan(workVec(i));
        });
      };

      test();
      getExecutionTime("kokkos::parallel_for transform optimized version", test);
    }

    Kokkos::finalize();
    std::cout << "\n";
}