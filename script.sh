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
	-d1) # -d1 option 
		
		awk -F';' '!seen[$1,$6]++ { count[$6]++ } END { for (name in count) print count[name],";"name }' $1 | sort -rn | head -n10 > temp/d1_data.data
gnuplot << EOF
		reset
		set terminal pngcairo size 800,1200 enhanced font "arial,12"
		set bars fullwidth
		set output "images/d1_output.png"
		set boxwidth 0.75
		set xlabel "Driver name" rotate by 180
		set y2label "Distances"
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
	display images/d1_output.png
		;;

	-d2)

		#awk -F';' '{distance[$6] += $5} END {for (name in distance) print name, distance[name]}' data.csv | sort -k3rn | head -n 10 > temp/d2_data.data

		;;
		*) echo "$arg n'existe pas";;
	esac
done







