sw5cc -host  main.c -c
sw5f90 -hybrid  main.o  -lxMath_manycore  -o ./app
bsub -I -b -q q_sw_expr -n 1 -cgsp 64  -host_stack 512 -share_size 6000 ./app
