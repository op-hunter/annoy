#!/bin/sh

for file in ./*
do
	echo $file
	tail -3 ${file}
	echo "_---------------------------------------------------"
done
