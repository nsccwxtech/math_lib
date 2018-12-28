sw5f90 -host -c main.o main.f90 
sw5f90 -hybrid -o app  main.o -lxMath_manycore
bsub -I -b -q q_sw_expr -n 1 -cgsp 64  -host_stack 512 -share_size 6000 ./app
