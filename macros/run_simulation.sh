#!/bin/bash

for i in {1..10}; do
	export OUTFILE="../output/run_output_$i.root"
	../build/sim ./run_beamOn.mac
done
