#!/bin/bash
# Must be executed in UCN-Simulations/code/
path_merge_file=../output/Beamline/merge/beamline_surface_TRIGA_merge.root
path_output_file=../output/Beamline/triga/
read -p "Make new histogram in $path_merge_file ? [Y / N] " -n 1 isNewFile
echo -e "\n"
if [ $isNewFile == "Y" ]
then
  echo Execute createHistogram
  ./bin/Release/createHistogram $path_merge_file <<EOF
  RECREATE
  2
  Initial_kinetic_energy_distribution
  hist_initial_ke
  100
  100e-9
  300e-9
  Final_kinetic_energy_distribution
  hist_final_ke
  100
  1e-11
  130e-9
EOF
fi
echo Execute addHistogram for initial kinetic energy
for file in `ls $path_output_file`;
do
  ./bin/Release/addHistogram $path_output_file$file $path_merge_file <<EOF
  hist_initial_ke
  component_track_world_DATA
  initial_kinetic_energy
EOF
done
echo Execute addHistogram for final kinetic energy
for file in `ls $path_output_file`;
do
  ./bin/Release/addHistogram $path_output_file$file $path_merge_file <<EOF
  hist_final_ke
  component_track_world_DATA
  final_kinetic_energy
EOF
done
