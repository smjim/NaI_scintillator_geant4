#!/bin/bash

for i in {0..999999}; do
    outfile_num=$(printf "%06d" "$i")  # format number with leading zeroes (6 digits)
    export OUTFILE="../output/Cs_Co_sources/run_output_${outfile_num}.root"
    #export OUTFILE="../output/Cs_source/run_output_${outfile_num}.root"
    ../build/sim ./run_beamOn.mac
done

