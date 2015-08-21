#!/bin/bash

SUBDIRS="
MatrixMultiplication
BinarySearch
FFT
"

for dir in $SUBDIRS
do
	cd $dir
	nohup ../../../../../bin/m2s --ctx-config ctx-config \
		--si-sim detailed --si-config ../si-config \
		--mem-config ../mem-si --net-config ../net-ideal-si \
		--net-report net.report \
		>nohup.out 2>&1 &
	cd ..
done
