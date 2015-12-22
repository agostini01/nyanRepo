unset origin
unset label
set term postscript eps enhanced color
set ticslevel 0
set nohidden3d
set size square
unset key
#set out "loads.ps"

#set label "Memory Snapshot - 10000 cycles - 1K Blocks" font "Helvetica,12" at screen 0.3, screen 0.15

set origin 0,-0.1
set view 0,0,0.5
#set view 30,40,0.5
set pm3d

set palette defined (0 "white", 0.0001 "black", 10 "gray", 60 "cyan", 100 "blue")
#set palette defined (0 "white",0.1 "gray", 5 "black")
set colorbox vertical user origin .2,.28 size 0.03, 0.26
unset surface

#set cbrange [0:1000]
set cbtics font "Helvettica, 6"
#set cblabel "Number of Accesses" font "Helvettica, 7"

set xlabel 'Time (cycles)' font "Helvettica, 7"
#set xrange [0:61008676]
#set xtics 0,10000000, 61008676 
#set mxtics 20
#set xrange [0:30000]
#set xtics 0,3000,30000 
set xtics font "Helvettica,6"
set xtics offset -0.5,-0.2

set ylabel 'Address (Hex)' rotate by 135 offset 2, 0 font "Helvettica, 7"
set ytics offset 1.5, 0
set format y "%.X"
#set yrange [0:4294967295]
#set ytics 0,536870912,4294967295
set ytics font "Helvettica,8"
#set yrange [0:36864]
#set ytics 0,4096,36864
set mytics 4

#set ztics font "Helvettica, 6"
unset ztics
#set zrange [0:10]
set label "Number of Accesses" font "Helvetica,7" at screen 0.27, screen 0.35 rotate by 90

splot "mem_snapshot_load_accesses" with lines

unset multiplot
