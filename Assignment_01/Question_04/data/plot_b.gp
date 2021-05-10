set grid
plot [-2:2] [] x**3-2*x+1 title "x^3 - 2x + 1", "output_b.dat" using 1:2:(sprintf("(%.2f, %d)",$1,$2)) with labels point  pt 7 offset char 1,1 title "roots"
set title "Plot showing roots of function x^3 - 2x + 1"
set xlabel "x"
set ylabel "x^3 - 2x + 1"
set terminal png
set output "plot_b.png"
replot
