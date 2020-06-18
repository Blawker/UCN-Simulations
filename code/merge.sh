#!/bin/bash
echo Make a new file ? [True / False]
read isNewFile
if [ $isNewFile == "True" ]
then
  echo Launch create_histogram
  ./bin/Release/create_histogram ../output/test_output.root <<EOF
  2
  Initial_kinetic_energy_distribution
  hist_initial_ke
  100
  1e-11
  300e-9
  Final_kinetic_energy_distribution
  hist_final_ke
  100
  1e-11
  120e-9
EOF
fi
echo Launch add_histogram for initial kinetic energy
for i in `seq 1 8`;
do
  ./bin/Release/add_histogram ../output/Beamline/beamline_surface_simulation_$i.root ../output/test_output.root <<EOF
  hist_initial_ke
  component_track_world_DATA
  initial_kinetic_energy
EOF
done
echo Launch add_histogram for final kinetic energy
for i in `seq 1 8`;
do
  ./bin/Release/add_histogram ../output/Beamline/beamline_surface_simulation_$i.root ../output/test_output.root <<EOF
  hist_final_ke
  component_track_world_DATA
  final_kinetic_energy
EOF
done
