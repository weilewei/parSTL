#include <commons.hpp>

#include<Kokkos_Core.hpp>

#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    Kokkos::initialize(argc,argv);

    {
      Kokkos::View<double*> workVec ("x", TEST_SIZE);
   
      for (long long i = 0 ; i < TEST_SIZE; ++i) 
        workVec(i) = uni(rng);

      getExecutionTime("kokkos::parallel_for transform", [&workVec]() mutable {                // (6)
        Kokkos::parallel_for("kokkos::parallel_for transform", TEST_SIZE, KOKKOS_LAMBDA (const int& i) {
          workVec(i) = std::tan(i);
        });
      });
    }

    Kokkos::finalize();
}