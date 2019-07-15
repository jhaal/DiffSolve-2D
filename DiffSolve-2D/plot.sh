#!/etc/alternatives/gnuplot -persist
reset
set terminal qt
# set size 1,1
# set multiplot
#fast
# set size 0.5
# set origin 0.05,0.5
# set view 50,20
# set title "Fast Flux Values"
# set xrange [0:10]
# set yrange [0:10]
# set zrange [0.90:1.0]
# set dgrid3d 90,90
# set hidden3d
# set xlabel "x-axis"
# set ylabel "y-axis"
# set zlabel "z-axis" offset 0.05
# set grid
# splot "fast.txt" matrix nonuniform
# splot  'fast.txt' using 2:3:4:5  every ::1  palette
# set dgrid3d 90,90
# splot 'fast.txt' every ::1:1 matrix nonuniform with image notitle
# set autoscale xfix
# set autoscale yfix
# set autoscale cbfix
# set pm3d map
# splot 'fast.txt' matrix nonuniform notitle

# set pm3d map
# splot 'fast.txt' matrix

#
# Demonstrate use of 4th data column to color a 3D surface.
# Also demonstrate use of the pseudodata special file '++'.
# This plot is nice for exploring the effect of the 'l' and 'L' hotkeys.
#
set view 49, 28, 1, 1.48
set xrange [ 0 : 10 ] noreverse nowriteback
set yrange [ 0 : 10 ] noreverse nowriteback
# set zrange [ 1.0 : 3.0 ] noreverse nowriteback
set ticslevel 0
set format cb "%4.1f"
set colorbox user size .03, .6 noborder
set cbtics scale 0

set samples 25, 25
set isosamples 50, 50

set title "4D data (3D Heat Map)"\
          ."\nIndependent value color-mapped onto 3D surface"  offset 0,1
set xlabel "x" offset 3, 0, 0 
set ylabel "y" offset -5, 0, 0
set zlabel "z" offset 2, 0, 0 
set pm3d implicit at s

# Z(x,y) = "fast.txt"
sinc(x,y) = sin(sqrt((x-20.)**2+(y-20.)**2))/sqrt((x-20.)**2+(y-20.)**2)
color(x,y) = 10. * (1.1 + sin((x-20.)/5.)*cos((y-20.)/10.))

splot 'fast.txt' using 1:2::(color($1,$2)) with pm3d title "4 data columns x/y/z/color"








# thermal
# set size 0.5
# set origin 0.5,0.5
# set title "Thermal Flux Values"
# set xrange [0:10]
# set yrange [0:10]
# set zrange [0.98:1.0]
# set dgrid3d 95,95 
# set hidden3d
# set xlabel "x-axis"
# set ylabel "y-axis"
# set zlabel "z-axis" offset 0.05 
# splot  "thermal.txt" matrix with lines title "Normalized Thermal Flux"

# k_eff
# set size 1,0.5
# set origin 0,0
# set title "k_{effective}"
# set xlabel"Number of iterations"
# set ylabel"k_{effective}"
# set xrange[0:120]
# set yrange[0.9:1.1]
# plot "keff.txt" u 1:2 with lines lw 1 lc 'red' title "k_{eff}", 1  lc 'black' title "k_{eff} = 1"
# unset multiplot
