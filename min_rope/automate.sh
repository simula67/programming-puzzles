#!/bin/bash
if [ $# -eq 0 -o $# -gt 1 ];
then
	echo "usage: $0 <number of ropes>"
	exit 1
fi
num_elements=$1
input="$num_elements\n"
for i in `seq 1 $num_elements`
do
    input="$input$i\n"
done
echo -ne $input|./min_rope

