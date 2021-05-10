set grid
plot [-2:2] [] x*exp(x) title "xe^x", "output_a.dat" using 1:2:(sprintf("(%.2f, %d)",$1,$2)) with labels point  pt 7 offset char 1,1 title "roots"
set title "Plot showing roots of function xe^x"
set xlabel "x"
set ylabel "xe^x"
set terminal png
set output "plot_a.png"
replot
