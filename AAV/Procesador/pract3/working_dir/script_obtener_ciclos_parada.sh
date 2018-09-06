#!/bin/bash

##### Variable a editar #####

EVENTS="mem_load_uops_retired:l1_miss,mem_load_uops_retired:l2_miss,mem_load_uops_retired:l3_miss"

#############################


Benchmark_list=('perlbench' 'gcc' 'bzip2' 'mcf' 'gobmk' 'hmmer' 'sjeng' 'libquantum' 'h264ref' 'omnetpp' 'astar' 'xalancbmk' 'bwaves' 'gamess' 'milc' 'zeusmp' 'gromacs' 'cactusADM' 'leslie3d' 'namd' 'dealII' 'soplex' 'povray' 'gemsFDTD' 'lbm')

sal=$(mktemp)
sal2=$(mktemp)


events_string=$(echo $EVENTS | sed 's/,/ /g')

echo "Benchmark Cycles Instructions" $events_string

for bench in 3 6 7 12 13 14 15 18 23 24; do

    ./monitoriza_aplicacion -W $bench -C 0 -e $EVENTS > $sal 2> $sal2

    cyc=$(cat $sal2 | grep "Final_count" | awk '{print $5}')
    ins=$(cat $sal2 | grep "Final_count" | awk '{print $7}')
    
    ev1=$(cat $sal2 | grep "Final_count" | awk '{print $9}')
    ev2=$(cat $sal2 | grep "Final_count" | awk '{print $11}')
    ev3=$(cat $sal2 | grep "Final_count" | awk '{print $13}')
    ev4=$(cat $sal2 | grep "Final_count" | awk '{print $15}')
    
    echo ${Benchmark_list[$bench]} $cyc $ins $ev1 $ev2 $ev3 $ev4
done