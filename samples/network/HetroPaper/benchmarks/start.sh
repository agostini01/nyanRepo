#!/bin/bash

SUBDIRS="
BlackScholes
DCT
DwtHaar1D
EigenValue
FastWalshTransform
FFT
FloydWarshall
Histogram
MatrixMultiplication
MatrixTranspose
MersenneTwister
PrefixSum
QuasiRandomSequence
RadixSort
RecursiveGaussian
Reduction
ScanLargeArrays
SimpleConvolution
SobelFilter
"

MAX_JOBS=2

for dir in $SUBDIRS
do
	while : ; 
	do
		num_m2s=$(ps -e | grep m2s | wc -l)
		if [ "$num_m2s" -lt "$MAX_JOBS" ]
		then
			break
		else
			sleep 100
		fi
	done

	echo "launching "$dir
	cd $dir
	nohup ../../../../../bin/m2s --ctx-config ctx-config \
		--si-sim detailed --si-config ../$1si-config.ini \
		--mem-config ../$1mem-si.ini --net-config ../$1net-si.ini \
		--net-report $2net.report \
		--mem-report $2mem.report \
    >$2nohup.out 2>&1 &
	cd ..
done


