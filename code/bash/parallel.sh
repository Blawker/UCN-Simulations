#!/bin/bash
# Must be executed in UCN-Simulations/code/bash

#!/bin/bash
# Must be executed in UCN-Simulations/code/

SECONDS=0
output_file="beamline_surface_slits_auto_simulation_triga_"
ext=".root"
# Absolute path
output_path="Software/UCN-Simulations/output/Beamline"
simulation_path="Software/Kasper_build"

seed="831"
output_folder="run2020Aug11_1"

cd
cd $simulation_path
pwd
echo "Output folder:" $output_path/$output_folder
read -p 'Run the simulation ? [Y / N] ' -n 1 isNewRun
echo -e "\n"
if [ $isNewRun == "Y" ]; then
        clear
        if [ -d "$output_path/$output_folder" ]; then
                echo "The folder" $output_folder "already exist in" $output_path
                echo ""
        else
                cd
                cd $output_path
                pwd
                rm -r $output_folder
                echo "Remove dir:" $output_folder
                mkdir $output_folder
                echo "Create dir:" $output_folder
                cd
                cd $simulation_path
                pwd
        fi

        echo "Launch parallelized simulation..."
        parallel --jobs 0 --dryrun  ./bin/Kassiopeia ../UCN-Simulations/config/Beamline/beamline_surface_slits_auto.xml -r random_seed=$seed{1}{2} output_file_name=$output_file{1}{2}$ext ::: {0..1} ::: {0..9}

        duration=$SECONDS

        # Merge of the output files
        cd
        cd $output_path/$output_folder
        if [ `ls -1 | wc -l` != 0 ]; then
                hadd -f beamline_surface_slits_TRIGA_merge_parallel.root `ls`
        fi
        ls -lh

        # Calcul the time of the simulation
        echo ""
        echo "Time of the simulation: $(($duration / 3600))h $(($duration / 60 % 60))min $(($duration % 60))s."
        echo "Stop: `date`"
fi
