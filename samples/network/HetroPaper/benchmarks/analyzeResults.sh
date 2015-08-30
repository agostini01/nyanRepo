SUBDIRS="BlackScholes
BoxFilter
DCT
DwtHaar1D
EigenValue
FFT
FastWalshTransform
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
SobelFilter"

for dir in $SUBDIRS
do
  printf "\n"$dir"\n"
  ./analyzeResult.py $dir
done
