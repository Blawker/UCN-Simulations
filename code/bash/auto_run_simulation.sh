#!/bin/bash
# Must be executed in UCN-Simulations/code/
SECONDS=0
seed="813"
output_file="beamline_surface_auto_simulation_triga_"
ext=".root"
cd ../../../Kassiopeia/Kasper_build
pwd
read -p 'Run the simulation ? [Y / N] ' -n 1 isNewRun
echo -e "\n"
if [ $isNewRun == "Y" ]
then
  for i in `seq 0 6`;
  do
    clear
    for j in `seq 0 9`;
    do
      clear
      ./bin/Kassiopeia.app/Contents/MacOS/Kassiopeia ../../Stage\ 2A\ -\ UCN\ -\ 2020/UCN-Simulations/config/Beamline/beamline_surface_auto.xml -r random_seed=$seed$i$j output_file_name=$output_file$i$j$ext &
    done
    wait
  done
  duration=$SECONDS

  # Merge of the output files
  cd ../../Stage\ 2A\ -\ UCN\ -\ 2020/UCN-Simulations/output/Beamline/auto_parallel/
  hadd -f ../merge/beamline_surface_TRIGA_merge_parallel.root `ls`

  # Calcul the time of the simulation
  echo ""
  echo "Time of the simulation: $(($duration / 3600))h $(($duration / 60))min $(($duration % 60))s."
  echo "Stop: `date`"
  #shutdown now
fi
