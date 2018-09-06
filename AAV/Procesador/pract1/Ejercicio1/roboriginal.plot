#!/bin/sh

resfile="rob.res"
figfile="rob.eps"
plotfile=$(mktemp)

cat << EOF > $plotfile
set term postscript eps
set size 0.5, 0.5
set key under
set xlabel 'ROB size'
set ylabel 'IPC'
set xrange [-0.5:6.5]
set xtics ( '4' 0, '8' 1, '16' 2, '32' 3, '64' 4, '128' 5, '256' 6)

plot '$resfile' every :::0::0 w linespoints t 'test-args',   \
     '$resfile' every :::1::1 w linespoints t 'test-printf', \
     '$resfile' every :::2::2 w linespoints t 'test-math',   \
     '$resfile' every :::3::3 w linespoints t 'test-sort'     
EOF

gnuplot $plotfile > $figfile
rm -f $plotfile
