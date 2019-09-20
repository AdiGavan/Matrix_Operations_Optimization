#!/bin/bash
module load compilers/gnu-5.4.0
make clean
make
rm -rf out1 out2 out3
./tema2_blas input
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
rm -rf out1 out2 out3
./tema2_neopt input
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
rm -rf out1 out2 out3
./tema2_opt_m input
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
rm -rf out1 out2 out3
./tema2_opt_f input
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
