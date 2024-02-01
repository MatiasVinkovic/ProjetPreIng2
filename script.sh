#!/bin/bash

echo "Hello mister Grignon, welcome in"
head -n17 draw.txt
#directory existence check
if [ ! -d "file" ];then #directory temp
	echo "no file directory detected : creation of it"
	mkdir file
	chmod u+r+w+x file
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

if [ -s "file" ];then	#if file is not empty : rm all its content but not itself
	#echo "temp file exists : rm its content"
	rm -r -f -d file/*
fi

if [ -s "images" ];then	#if images is not empty : rm all its content but not itself
	#echo "temp file exists : rm its content"
	rm -r -f -d images/*
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
	echo "$1 is not a .csv file"
	exit 9
fi


# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'  # No Color

dollar_at=$@ #all the args of the line

for arg in ${dollar_at#*" "}
do
	case $arg in
	-h) 
	tail -n8 draw.txt
	cat help.txt
	exit 5
	;;
	--troll) cat dontOpen.txt ;;	
	esac
done

for arg in ${dollar_at#*" "}
do
	case $arg in 
	--bogoss) echo "vous êtes un énorme bogoss, aucun doute sur ça";;
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

		set autoscale y
		set yrange [0:*]

		set ytics rotate
		set datafile separator ";"
		plot for [COL=1:1] "temp/d1_data.data" using COL:xticlabel(2) lc rgb "blue"
EOF
	END=$(date +%s)
	DIFF=$(( $END - $START ))
	echo -e "${YELLOW}It took $DIFF seconds${NC}"
	#sudo apt install 	imagemagick : to manipulate images in shell
	convert -rotate 90 images/d1_output.png images/d1_output.png
	#display images/d1_output.png
		;;

	-d2)
	START=$(date +%s)
		LC_NUMERIC=en_US.UTF-8 awk -F';' '{distance[$6] += $5} END {for (name in distance) print distance[name],";"name }' $1 | sort -k1rn | head -n 10 > temp/d2_data.data
gnuplot << EOF
		reset
		set terminal pngcairo size 800,1200 enhanced font "arial,12"
		set bars fullwidth
		set output "images/d2_output.png"
		set boxwidth 0.75
		set xlabel "Driver name" rotate by 180
		set y2label "Distances (in km)"
		
		set ytics rotate
		set ylabel "option -d2 : Distance = f(Driver)"
		set style data histogram
		set style fill solid 1.0 border 
		set style histogram rowstacked
		set xtics rotate

		set autoscale y
		set yrange [0:*]

		set datafile separator ";"
		plot for [COL=1:1] "temp/d2_data.data" using COL:xticlabel(2) lc rgb "#308c1f" title "" 
EOF
	convert -rotate 90 images/d2_output.png images/d2_output.png
	#display images/d2_output.png
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo -e "${YELLOW}It took $DIFF seconds${NC}"
		;;

	-l)		
		START=$(date +%s)																																									 #put r to have same as the teacher				
		LC_NUMERIC=en_US.UTF-8 awk -F';' '{distance[$1] += $5} END {for (routeID in distance) print distance[routeID],";"routeID}' $1 | sort -k1n | tail -n 10 | sort -t';' -k2n > temp/l_data.data
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo -e "${YELLOW}It took $DIFF seconds${NC}"
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
		set ytics rotate
		set autoscale y
		
		set yrange [0:*]
		plot "temp/l_data.data" using 1:xticlabels(2) lc rgb "#308c1f" with boxes title ""
EOF
	#display images/d2_output.png
		
		;;
	-s)	
		START=$(date +%s)
		cat $1 | cut -d';' -f1,5 | tail -n +2 | sed 's/;/ /g' > file/option_s_data.txt
		
		echo "S treatment launching ..."
		cd progC/option_s/
		echo "MakeFile Initialisation in process..."
		echo -e "${RED}"
		if [ ! -e "prog" ];then
			make
		fi;
		echo -e "${GREEN}MakeFile succesfully finished${NC}"
		./prog
		cd ../../
		cd file/
		tail -50 option_s_final_file.txt | tac > option_s.data	
		rm option_s_data.txt
		rm option_s_final_file.txt
		#cat option_s.data 
		nl -s';' -w1 -nrz option_s.data > s_data.data #put the line number : CANT DO IT WITH INFIX AND COUNT WTF
		rm option_s.data

		
		#And also manage the Gnuplot file and attempt to separate the Gnuplot scripts as done.		
		cd ..
		cd gnuplot_file/
		chmod u+r+w+x option_s_gnuplot.sh
		./option_s_gnuplot.sh

		echo "S is over"
		cd ..
		cd progC/option_s/
		make clean
		cd ../../
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo -e "${YELLOW}It took $DIFF seconds${NC}"
															 			
	;;

	-t)	
		START=$(date +%s)
		cat $1 | sed 's/ /-/g' | sed 's/;/ /g' | cut -d' ' -f1-4 | tail -n +2 > file/option_t_data.txt
		
		echo "T treatment launching ..."
		cd progC/option_t/
		echo "MakeFile Initialisation in process..."
		echo -e "${RED}"
		if [ ! -e "prog" ];then
			make
		fi;
		echo -e "${GREEN}"
		echo "Make file succesfully finished"
		./prog
		cd ../../
		cd file/
		#cat t_data.data
		rm option_t_data.txt option_t_final_file_10.txt option_t_final_file_not_10.txt
		#cat option_s.data 
		cd ..
		cd gnuplot_file/
		chmod u+r+w+x option_t_gnuplot.sh
		./option_t_gnuplot.sh

		echo "T is over"
		cd ..
		cd progC/option_t/
		make clean
		cd ../../
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		echo -e "${YELLOW}It took $DIFF seconds${NC}"
		
													 			
	;;



		*) echo -e "${RED}$arg n'existe pas${NC}";;
	esac
done

if [ "$help_detected" = true ]; then
    cat help.txt
    exit 0
fi
