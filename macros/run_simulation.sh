#!/bin/bash

for i in {0..999999}; do
    outfile_num=$(printf "%06d" "$i")  # format number with leading zeroes (6 digits)
    export OUTFILE="../output/run_output_${outfile_num}.root"
    ../build/sim ./run_beamOn.mac
done

