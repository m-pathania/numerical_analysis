set grid
set datafile separator ","
set key outside
plot [0:8] [] "differences_2.dat" using 1:2 with lines title "arctan(x)" lw 2, '' using 1:3 with lines title "2^{nd} degree" lw 3
set title "2^{nd} degree newton form polynomial for interpolation"
set xlabel "x"
set ylabel "y"
set terminal png
set output "plot_2nd.png"
replot

plot [0:8] [] "differences_4.dat" using 1:2 with lines title "arctan(x)" lw 2, '' using 1:3 with lines title "4^{th} degree" lw 3
set title "4^{th} degree newton form polynomial for interpolation"
set xlabel "x"
set ylabel "y"
set terminal png
set output "plot_4th.png"
replot

plot [0:8] [] "differences_10.dat" using 1:2 with lines title "arctan(x)" lw 2, '' using 1:3 with lines title "10^{th} degree" lw 3
set title "10^{th} degree newton form polynomial for interpolation"
set xlabel "x"
set ylabel "y"
set terminal png
set output "plot_10th.png"
replot

plot [0:8] [] "differences_2.dat" using 1:2 with lines title "arctan(x)" lw 2,'' using 1:3 with lines title "2^{nd} degree" lw 3, 'differences_4.dat' using 1:3 with lines title "4^{th} degree" lw 3, 'differences_10.dat' using 1:3 with lines title "10^{th} degree" lw 3
set title "all newton form polynomial for interpolation"
set xlabel "x"
set ylabel "y"
set terminal png
set output "plot_all.png"
replot
