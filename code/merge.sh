#!/bin/bash
# Must be executed in UCN-Simulations/code/

cd ../output/Beamline/auto_parallel/
hadd -f ../merge/beamline_surface_TRIGA_merge_parallel.root `ls`
