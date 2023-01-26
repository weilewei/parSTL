module purge
source /opt/cray/pe/cpe/22.11/restore_system_defaults.sh

module load gcc/11.2.0

mkdir -p build && cd build
make clean
cmake -DCMAKE_BUILD_TYPE=Release ..
make

cd /global/homes/w/wwei/src/parSTL/build
./nvc/nvcPar
./hpx/hpxPar --hpx:threads=64 
OMP_NUM_THREADS=64 OMP_PLACES=threads OMP_PROC_BIND=close ./kokkos/kokkosPar 
./std/stdPar
./gnu/gnuPar

