#!/bin/bash


#directory existence check

if [ ! -d "temp" ];then #directory temp
	echo "no temp directory detected : creation of it"
	mkdir temp
	chmod u+r+w+x temp
fi

if [ ! -d "images" ];then #directory images
	echo "no images directory detected : creation of it"
	mkdir images
	chmod u+r+w+x images
fi

if [ -s "temp" ];then	#if temp is not empty : rm all its content but not itself
	#echo "temp file exists : rm its content"
	rm -r -f -d temp/*
fi

if (($# <= 1)) ; then	#check if at least 1 argument
	echo "missing arguments (-d1;-d2...)"
	exit 1
fi

if [ ! -f $1 ] ; then
	echo "$1 n'est pas un fichier"
	exit 2
fi

if [[ ! $1 == *.csv ]];then
	echo "pas un fichier csv"
	exit 9
fi

dollar_at=$@ #all the args of the line

for arg in ${dollar_at#*" "}
do
	case $arg in 
	--help) echo "timo est bogoss tout autant que ahmed, ainsi que matias";;
	--bogoss) echo "vous etes un enorme bogoss";;
	-d1) # -d1 option 
		
		awk -F';' '!seen[$1,$6]++ { count[$6]++ } END { for (name in count) print count[name],";"name }' $1 | sort -rn | head -n10 > temp/d1_data.data
gnuplot << EOF
		reset
		set terminal pngcairo size 800,1200 enhanced font "arial,12"
		set bars fullwidth
		set output "images/d1_output.png"
		set boxwidth 0.75
		set xlabel "Driver name" rotate by 180
		set y2label "Number of travels"
		set ylabel "option -d1 : Nb routes = f(Driver)"
		set style data histogram
		set style fill solid 1.0 border 
		set style histogram rowstacked
		set xtics rotate
		set y2tics rotate
		set y2range [0:250]
		set datafile separator ";"
		plot for [COL=1:2] "temp/d1_data.data" using COL:xticlabel(2) lc rgb "blue"
EOF
	#sudo apt install 	imagemagick : to manipulate images in shell
	convert -rotate 90 images/d1_output.png images/d1_output.png
	#display images/d1_output.png
		;;

	-d2)
		LC_NUMERIC=en_US.UTF-8 awk -F';' '{distance[$6] += $5} END {for (name in distance) print distance[name],";"name }' data.csv | sort -k1rn | head -n 10 > temp/d2_data.data
gnuplot << EOF
		reset
		set terminal pngcairo size 800,1200 enhanced font "arial,12"
		set bars fullwidth
		set output "images/d2_output.png"
		set boxwidth 0.75
		set xlabel "Driver name" rotate by 180
		set y2label "Distances (in km)"
		set y2range [0:160000]
		set y2tics rotate
		set ylabel "option -d2 : Distance = f(Driver)"
		set style data histogram
		set style fill solid 1.0 border 
		set style histogram rowstacked
		set xtics rotate
		set datafile separator ";"
		plot for [COL=1:2] "temp/d2_data.data" using COL:xticlabel(2) lc rgb "#308c1f" title "" 
EOF
	convert -rotate 90 images/d2_output.png images/d2_output.png
	#display images/d2_output.png

		;;

	-l)																																											 #put r to have same as the teacher				
		LC_NUMERIC=en_US.UTF-8 awk -F';' '{distance[$1] += $5} END {for (routeID in distance) print distance[routeID],";"routeID}' data.csv | sort -k1n | tail -n 10 | sort -t';' -k2n > temp/l_data.data
gnuplot << EOF
		reset
		set terminal pngcairo size 800,800 enhanced font "arial,12"
		set output "images/l_output.png"
		set x2label "Option -l : Distance = f(Route)" 
		set ylabel "Distance (Km)" rotate by 90
		set boxwidth 0.75
		set style data histogram
		set style fill solid 1.0 border
		set style histogram rowstacked
		set datafile separator ";"
		set yrange [0:3000]
		set ytics 0,500,3000
		plot "temp/l_data.data" using 1:xticlabels(2) lc rgb "#308c1f" with boxes title ""
EOF
	#display images/d2_output.png

		;;

		*) echo "$arg n'existe pas";;
	esac
done







