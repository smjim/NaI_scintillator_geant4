#!/bin/bash

for i in {0..999}; do
    outfile_num=$(printf "%03d" "$i")  # format number with leading zeroes (3 digits)
    export OUTFILE="../output/run_output_${outfile_num}.root"
    ../build/sim ./run_beamOn.mac
done

