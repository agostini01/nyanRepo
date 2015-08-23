#!/bin/bash

SUBDIRS="
AESEncryptDecrypt
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
		--si-sim detailed --si-config ../si-config \
		--mem-config ../mem-si --net-config ../net-ideal-si \
		--net-report net.report \
		--mem-report mem.report \
		>nohup.out 2>&1 &
	cd ..
done
