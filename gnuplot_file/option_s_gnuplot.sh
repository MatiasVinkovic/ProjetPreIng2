#!/bin/bash

cd ..	#back into file directory


gnuplot << EOF
	reset
	set terminal pngcairo size 1200,800 enhanced font "arial,12"
	set output "images/s_output.png"
	set x2label "Option -s : Distance = f(Route)" 
 	set xlabel "RouteID"
	set ylabel "Distance (Km)" rotate by 90
	set ytics 100
	set xtics rotate by 45 right
	set title "Graphique Min-Max-Moyenne"
	set autoscale y
	set yrange [0:*]
	set datafile separator ';'
	plot 'file/s_data.data' using 0:3:5:xticlabels(2) with filledcurves linecolor 4 lt 1 title 'Distance Max(Km))',\
			''using 0:4 with lines linecolor 0 title 'Distance average (km)'
EOF
