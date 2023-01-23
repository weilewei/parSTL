module purge
source /opt/cray/pe/cpe/22.11/restore_lmod_system_defaults.sh
module load nvhpc/22.9

mkdir -p build && cd build
make clean
cmake ..
make

./nvc/nvcPar
./hpx/hpxPar
OMP_PLACES=threads OMP_PROC_BIND=spread ./kokkos/kokkosPar 
./std/stdPar

