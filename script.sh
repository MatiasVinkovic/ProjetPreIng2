#!/bin/bash

#directory existence check
if [ ! -d "file" ];then #directory temp
	echo "no file directory detected : creation of it"
	mkdir file
	chmod u+r+w+x temp
fi


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
	echo "missing arguments (-d1;-d2;-l;-s;-t)"
	exit 1
fi

if [ ! -f $1 ] ; then
	echo "$1 is not a file"
	exit 2
fi

if [[ ! $1 == *.csv ]];then
	echo "is not a .csv file"
	exit 9
fi

dollar_at=$@ #all the args of the line

for arg in ${dollar_at#*" "}
do
	case $arg in 
	--help) echo "timo est bogoss tout autant que ahmed, ainsi que matias";;
	--bogoss) echo "vous etes un enorme bogoss";;
	-d1) # -d1 option 
		START=$(date +%s)
		awk -F';' '!seen[$1,$6]++ { count[$6]++ } END { for (name in count) print count[name],";"name }' $1 | sort -rn | head -n10 > temp/d1_data.data
		#cut -d';' -f1,6 "$1" | awk -F';' '!arr[$1]++ {arr2[$2]++} END {for (i in arr2) printf "%s:%d\n",i,arr2[i]}' | sort -t';' -k2nr | head -n10 > temp/d1_data.data
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
	END=$(date +%s)
	DIFF=$(( $END - $START ))
	echo "It took $DIFF seconds"
	#sudo apt install 	imagemagick : to manipulate images in shell
	convert -rotate 90 images/d1_output.png images/d1_output.png
	#display images/d1_output.png
		;;

	-d2)
	START=$(date +%s)
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
		plot for [COL=1:1] "temp/d2_data.data" using COL:xticlabel(2) lc rgb "#308c1f" title "" 
EOF
	convert -rotate 90 images/d2_output.png images/d2_output.png
	#display images/d2_output.png
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo "It took $DIFF seconds"
		;;

	-l)		
		START=$(date +%s)																																									 #put r to have same as the teacher				
		LC_NUMERIC=en_US.UTF-8 awk -F';' '{distance[$1] += $5} END {for (routeID in distance) print distance[routeID],";"routeID}' data.csv | sort -k1n | tail -n 10 | sort -t';' -k2n > temp/l_data.data
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo "It took $DIFF seconds"
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
	-s)	
		cat data.csv | cut -d';' -f1,5 | tail -n +2 | sed 's/;/ /g' > file/option_s_data.txt
		# we want to put the number of lines into the c programmn but with
		# wc -l, it prints the file name, so we use a combinaison of find and cat to
		# keep only the number of lines, we never know if a bug could happened
		t=`find file/option_s_data.txt -type f -exec cat {} + | wc -l`
		echo "t is $t"
		
		cd progC/
		gcc option_s.c -o prog -lm
		./prog $t
		cd ../
		cd file/
		tail -50 option_s_final_file.txt | tac > option_s.data	
		rm option_s_data.txt
		rm option_s_final_file.txt
		#cat option_s.data 
		nl -s';' -w1 -nrz option_s.data > s_data.data #put the line number : CANT DO IT WITH INFIX AND COUNT WTF
		rm option_s.data

		#il faut encore modifier le "oui.data"
		#ainsi que gerer le fichier gnuplot et essayer de separer les scripts gnuplot comme fait
		cd ..
		cd gnuplot_file/
		chmod u+r+w+x option_s_gnuplot.sh
		./option_s_gnuplot.sh

		echo "traitement S terminé"
		cd ..
		#display images/s_output.png
															 			
	;;

	-t)	
		cat data.csv | sed 's/ /-/g' | sed 's/;/ /g' | cut -d' ' -f1-4 | tail -n +2 > file/option_t_data.txt
		# we want to put the number of lines into the c programmn but with
		# wc -l, it prints the file name, so we use a combinaison of find and cat to
		# keep only the number of lines, we never know if a bug could happened
		t=`find file/option_t_data.txt -type f -exec cat {} + | wc -l`
		echo "t is $t"

		cd progC/
		gcc option_t.c -o prog -lm
		./prog $t
		cd ../
		cd file/
		cat t_data.data
		rm option_t_data.txt option_t_final_file_10.txt option_t_final_file_not_10.txt
		#cat option_s.data 

		cd ..
		cd gnuplot_file/
		chmod u+r+w+x option_t_gnuplot.sh
		./option_t_gnuplot.sh

		echo "traitement T terminé"
		cd ..
		
													 			
	;;



		*) echo "$arg n'existe pas";;
	esac
done
