#define USE_KOKKOS
//#define USE_STD

#include<type_traits>
#include<chrono>

#ifdef USE_KOKKOS
#include <Kokkos_Core.hpp>
#include <Kokkos_StdAlgorithms.hpp>
#define LAMBDA __host__ __device__
using Kokkos::Experimental::transform;
using Kokkos::Experimental::transform_reduce;
using Kokkos::Experimental::begin;
using Kokkos::Experimental::end;
using std::plus;
#endif

#ifdef USE_STD
#define __PSTL_PAR_BACKEND_TBB 0
#include<algorithm>
#include<numeric>
#include<execution>
#define LAMBDA
using std::transform;
using std::transform_reduce;
using std::begin;
using std::end;
using std::plus;
#endif
#include <cmath>

template<class Exec, class V1, class V2, class T>
void run_test(Exec exec, V1& a, V2& b, T add_some) {
  transform(exec, begin(a), end(a), begin(a), begin(b), [=] LAMBDA (const T& v1, const T& v2) -> T { return v1 + v2; });
  T sum = transform_reduce(exec, begin(a), end(a), begin(b), add_some, plus<T>{}, [=] LAMBDA (const T& v1, const T& v2) -> T { return v1 * v2; });
  transform(exec, begin(a), end(a), begin(a), [=] LAMBDA (const T& v1) -> T { return v1/sum; });
  transform(exec, begin(b), end(b), begin(b), [=] LAMBDA (const T& v2) -> T { return v2/sum; });
}

class Timer {
 private:
  std::chrono::high_resolution_clock::time_point m_old;

 public:
  inline void reset() { m_old = std::chrono::high_resolution_clock::now(); }

  inline ~Timer() = default;

  inline Timer() { reset(); }

  Timer(const Timer&);
  Timer& operator=(const Timer&);

  inline double seconds() const {
    std::chrono::high_resolution_clock::time_point m_new =
        std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double> >(m_new -
                                                                      m_old)
        .count();
  }
};

#ifdef USE_KOKKOS
using exec_t = Kokkos::DefaultExecutionSpace;
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    int N = argc > 1 ? atoi(argv[1]) : 1000000;
    int R = argc > 2 ? atoi(argv[2]) : 10;

    Kokkos::View<double*> a("A",N); Kokkos::View<double*> b("B",N);

    Timer timer;
    run_test(Kokkos::DefaultExecutionSpace(), a, b, 0.);
    double time = timer.seconds();
    printf("1. Run -- Time: %e GB/s: %e\n", time,1.e-9*N*8*(3+2+2+2)/time);

    timer.reset();
    run_test(Kokkos::DefaultExecutionSpace(), a, b, 0.);
    time = timer.seconds(); 
    printf("2. Run -- Time: %e GB/s: %e\n", time,1.e-9*N*8*(3+2+2+2)/time);
  } 
  Kokkos::finalize();
} 
#endif

#ifdef USE_STD
int main(int argc, char* argv[]) {
  { 
    int N = argc > 1 ? atoi(argv[1]) : 1000000;
    int R = argc > 2 ? atoi(argv[2]) : 10;
    
    std::vector<double> a(N); std::vector<double> b(N);
    
    Timer timer;
    run_test(std::execution::par, a, b, 0.);
    double time = timer.seconds();
    printf("1. Run -- Time: %e GB/s: %e\n", time,1.e-9*N*8*(3+2+2+2)/time);
    
    timer.reset();
    run_test(std::execution::par, a, b, 0.);
    time = timer.seconds();
    printf("2. Run -- Time: %e GB/s: %e\n", time,1.e-9*N*8*(3+2+2+2)/time);
  }
}
#endif