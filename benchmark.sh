#!/bin/bash


find ${1} -name "input-pairs-*.txt"|while read fname; do
	for i in {1..1} 
		do
			echo "Running ${2} $fname"
			${2} $fname 
		done
done

