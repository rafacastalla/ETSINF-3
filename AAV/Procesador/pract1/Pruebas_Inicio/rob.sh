#!/bin/sh
resfile="rob.res"
tempfile=$(mktemp)
rm -f $resfile
for workload in test-args.i386 test-printf.i386 test-math.i386 test-sort.i386
do
	for robsize in 4 8 16 32 64 128 256
	do
		./m2s -rob_size $robsize $workload > /dev/null 2> $tempfile
		line=$(cat $tempfile | grep sim.ipc)
		ipc=$(echo $line | awk '{print $2}')
		echo $ipc >> $resfile
		echo "$workload: simulacion con ROB de tamanyo $robsize terminada"
	done
	echo >> $resfile
	echo
done
echo
