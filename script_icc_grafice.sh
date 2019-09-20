#!/bin/bash
module load utilities/intel_parallel_studio_xe_2016
make -f Makefile.icc clean
make -f Makefile.icc
./tema2_neopt input_custom_grafice
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
./tema2_blas input_custom_grafice
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
./tema2_opt_m input_custom_grafice
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
./tema2_opt_f input_custom_grafice
./compare out1 /export/asc/tema2/out1 0.00001
./compare out2 /export/asc/tema2/out2 0.00001
./compare out3 /export/asc/tema2/out3 0.00001
