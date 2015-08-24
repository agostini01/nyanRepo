#!/bin/bash

SUBDIRS="
AESEncryptDecrypt
BinarySearch
BinomialOption
BitonicSort
BlackScholes
BoxFilter
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

for dir in $SUBDIRS
do
	cd $dir
	nohup ../../../../../bin/m2s --ctx-config ctx-config \
		--si-sim detailed --si-config ../$1si-config \
		--mem-config ../$1mem-si --net-config ../$1net-ideal-si \
		--net-report $2net.report \
		--mem-report $2mem.report \
		>$2nohup.out 2>&1 &
	cd ..
done
