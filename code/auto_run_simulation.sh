#!/bin/bash
# Must be executed in UCN-Simulations/code/
seed="8130"
output_file="beamline_surface_auto_simulation_"
ext=".root"
cd ../../../Kassiopeia/Kasper_build
pwd
read -p 'Run the simulation ? [Y / N] ' -n 1 isNewFile
echo -e "\n"
if [ $isNewFile == "Y" ]
then
  for i in `seq 1 5`;
  do
    ./bin/Kassiopeia.app/Contents/MacOS/Kassiopeia ./../../Stage\ 2A\ -\ UCN\ -\ 2020/UCN-Simulations/config/Beamline/beamline_surface_auto.xml -r random_seed=$seed$i output_file_name=$output_file$i$ext
  done
fi
