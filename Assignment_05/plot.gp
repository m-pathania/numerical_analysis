set grid
set datafile separator ","
set key outside
plot "output_n_2.dat" using 1:2 with lines title "n = 2" lw 2, "output_n_5.dat" using 1:2 with lines title "n = 5" lw 2, "output_n_10.dat" using 1:2 with lines title "n = 10" lw 2, "output_n_50.dat" using 1:2 with lines title "n = 50" lw 2, "output_n_100.dat" using 1:2 with lines title "n = 100" lw 2, "output_n_500.dat" using 1:2 with lines title "n = 500" lw 2, "output_n_1000.dat" using 1:2 with lines title "n = 1000" lw 2, "output_n_2000.dat" using 1:2 with lines title "n = 2000" lw 2
set title "plot for different values of n"
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_x(t).png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_10.dat" using 1:2 with lines title "n = 10" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_10.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_2.dat" using 1:2 with lines title "n = 2" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_2.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_5.dat" using 1:2 with lines title "n = 5" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_5.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_50.dat" using 1:2 with lines title "n = 50" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_50.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_100.dat" using 1:2 with lines title "n = 100" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_100.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_500.dat" using 1:2 with lines title "n = 500" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_500.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_1000.dat" using 1:2 with lines title "n = 1000" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_1000.png"
replot

set terminal qt
set grid
set datafile separator ","
set key outside
plot "output_n_2000.dat" using 1:2 with lines title "n = 2000" lw 2
set title ""
set xlabel "t"
set ylabel "x"
set terminal png
set output "plot_n_2000.png"
replot