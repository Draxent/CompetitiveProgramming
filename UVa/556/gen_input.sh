#!/bin/bash

if [ $# -lt 2 ]; then
	echo "Usage: $0 width height"
	exit 1
fi

WIDTH=$1
HEIGHT=$2
START=0

echo "$HEIGHT $WIDTH"

for (( i = 0; i < $HEIGHT; i++ ))
do
	# IT ENSURE THAT THE ROBOT CAN DO AT LEAST ONE STEP
	if [ $i -eq $(( $HEIGHT-1 )) ]; then
		START=2
		echo -n "00"
	fi

	# GENERETE THE STRUCTURE OF THE MAZE
	for (( j = $START; j < $WIDTH; j++ ))
	do
		# RANDOM GOES FROM 1 TO 32767. Probability ~4/5
		if [ $RANDOM -lt 25000 ]; then
			echo -n "0"
		else
			echo -n "1"
		fi
	done
	# NEW LINE
	echo
done

echo "0 0"

