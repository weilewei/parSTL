module purge
source /opt/cray/pe/cpe/22.11/restore_lmod_system_defaults.sh
module load nvhpc/22.9

export CC=/global/homes/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/gcc-11.2.0-zvvuszlajgsejuuf5o25rceihybuakbo/bin/gcc
export CXX=/global/homes/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/gcc-11.2.0-zvvuszlajgsejuuf5o25rceihybuakbo/bin/g++

mkdir -p build && cd build
make clean
cmake ..
make

./nvc/nvcPar
./hpx/hpxPar
OMP_PLACES=threads OMP_PROC_BIND=spread ./kokkos/kokkosPar 
./std/stdPar

