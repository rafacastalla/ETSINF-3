#!/bin/sh
#40 ENTROS 40 C.F
resfile="rob.res"
tempfile=$(mktemp)
#Creamos 5 ficheros .res de resultados por cada programa de prueba
for workload in test-args.i386 test-printf.i386 test-math.i386 test-sort.i386
do
	resfile="$workload.res"
	rm -f $resfile
	echo "Guardando en : $resfile"
	for iqsize in 4 8 16 32 64 #cola de instrucciones
	do
		for rfsize in 32 36 44 60 92 #banco de registros fısico
		do
		  ./m2s -iq_size $iqsize -rf_int_size $rfsize -rf_fp_size $rfsize $workload > /dev/null 2> $tempfile
		  line=$(cat $tempfile | grep sim.ipc)
		  ipc=$(echo $line | awk '{print $2}')
		  echo $ipc >> $resfile
		  echo "$workload: simulacion con BANCO DE REGISTRO de tamanyo $rfsize con COLA INST: $iqsize  terminada"
		done
		echo >> $resfile
	done
	echo
done
echo
