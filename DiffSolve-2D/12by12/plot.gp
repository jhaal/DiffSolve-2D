reset
set term eps enhanced
set output "fast.eps"
set title  "3D surface from a grid (matrix) of fast flux values"
set xrange [0:10]
set yrange [0:10]
set zrange [0.95:1.0]
set dgrid3d 95,95
set hidden3d
set xlabel  "Core Dimension Along x-axis" offset 0,-1,0 rotate parallel
set ylabel  "Core Dimension Along y-axis" offset 0,-1,0 rotate parallel
set zlabel  "Fast Flux" offset -1,0,0 rotate parallel
splot "fast.txt" matrix with lines title "Normalized Fast Flux"
set output


reset
set term eps enhanced
set output "thermal.eps"
set title  "3D surface from a grid (matrix) of thermal flux values"
set xrange [0:10]
set yrange [0:10]
set zrange [0.95:1.0]
set dgrid3d 95,95
set hidden3d
set xlabel  "Core Dimension Along x-axis" offset 0,-1,0 rotate parallel
set ylabel  "Core Dimension Along y-axis" offset 0,-1,0 rotate parallel
set zlabel  "Fast Flux" offset -1,0,0 rotate parallel
splot "thermal.txt" matrix with lines title "Normalized Thermal Flux"
set output


reset
set term eps enhanced
set output "k_eff.eps"
set title  "Plot of k_{effective} with number of iterations"
set xlabel  "Number of iterations"
set ylabel  "k_{effective}"
set xrange[0:200]
set yrange[0.9:1.1]
plot "keff.txt" u 1:2 with lines lw 1 lc 'red' title "k_{eff}", 1  lc 'black' title "k_{eff} = 1"
set output


reset
set terminal qt persist size 700,700
set size 1,1
set multiplot

set size 0.5
set origin 0.05,0.5
set title "Fast Flux Values "
set xrange [0:10]
set yrange [0:10]
set zrange [0.95:1.0]
set dgrid3d 95,95
set hidden3d
set xlabel "x-axis"
set ylabel "y-axis"
set zlabel "z-axis" offset 0.05
splot "fast.txt" matrix with lines title "Normalized Fast Flux"

set size 0.5
set origin 0.5,0.5
set title "Thermal Flux Values"
set xrange [0:10]
set yrange [0:10]
set zrange [0.98:1.0]
set dgrid3d 95,95
set hidden3d
set xlabel "x-axis"
set ylabel "y-axis"
set zlabel "z-axis" offset 0.05 
splot  "thermal.txt" matrix with lines title "Normalized Thermal Flux"

set size 1,0.5
set origin 0,0
set title "k_{effective}"
set xlabel "Number of iterations"
set ylabel "k_{effective}"
set xrange[0:120]
set yrange[0.9:1.1]
plot "keff.txt" u 1:2 with lines lw 1 lc 'red' title "k_{eff}", 1  lc 'black' title "k_{eff} = 1"
unset multiplot
