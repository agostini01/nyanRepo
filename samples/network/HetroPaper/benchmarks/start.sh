#!/bin/bash

SUBDIRS="
MatrixMultiplication
BinarySearch
BinomialOption
BitonicSort
BlackScholes
FFT
FloydWarshall
"

for dir in $SUBDIRS
do
	cd $dir
	nohup ../../../../../bin/m2s --ctx-config ctx-config \
		--si-sim detailed --si-config $1si-config \
		--mem-config $1mem-si --net-config $1net-ideal-si \
		--net-report net.report \
		--mem-report mem.report \
		>nohup.out 2>&1 &
	cd ..
done
