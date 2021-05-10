set grid
plot [-2:2] [] (sin(x) - (1.0/x)) title "sin(x) - 1/x", "output_c.dat" using 1:2:(sprintf("(%.2f, %d)",$1,$2)) with labels point  pt 7 offset char 1,1 title "roots"
set title "Plot showing roots of function sin(x) - 1/x"
set xlabel "x"
set ylabel "sin(x) - 1/x"
set terminal png
set output "plot_c.png"
replot
