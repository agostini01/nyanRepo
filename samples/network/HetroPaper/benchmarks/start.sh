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
		--net-report net.report \
		--mem-report mem.report \
		>nohup.out 2>&1 &
	cd ..
done
