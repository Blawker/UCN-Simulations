#!/bin/bash
path_output_file=../output/test_output.root
echo Make new histogram in $path_output_file ? [Y / N]
read isNewFile
if [ $isNewFile == "Y" ]
then
  echo Execute create_histogram
  ./bin/Release/create_histogram $path_output_file <<EOF
  RECREATE
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
  130e-9
EOF
fi
echo How many files to add ?
read n
echo Execute add_histogram for initial kinetic energy
for i in `seq 1 $n`;
do
  ./bin/Release/add_histogram ../output/Beamline/beamline_surface_simulation_$i.root $path_output_file <<EOF
  hist_initial_ke
  component_track_world_DATA
  initial_kinetic_energy
EOF
done
echo Execute add_histogram for final kinetic energy
for i in `seq 1 $n`;
do
  ./bin/Release/add_histogram ../output/Beamline/beamline_surface_simulation_$i.root $path_output_file <<EOF
  hist_final_ke
  component_track_world_DATA
  final_kinetic_energy
EOF
done
