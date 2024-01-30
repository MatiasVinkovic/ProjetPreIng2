#!/bin/bash

cd ..

gnuplot << EOF
	reset
	set terminal pngcairo enhanced font "arial,10" size 800,600
	set output "images/t_output.png"

	set style data histograms
	set style fill solid 1.00 border 0
	set style histogram clustered gap 7
	set boxwidth 3
	set title "Option -t : Number routes = f(Towns)"
	set xlabel "Towns"
	set ylabel "Nombre routes"
	set xtics rotate by -45
	set datafile separator ";"
	plot 'file/t_data.data' using 2:xtic(1) lc rgb "#36b83b" title "Total routes", '' using 3 lc rgb "#207523" title "First Town"
EOF
