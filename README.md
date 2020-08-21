# UCN-Simulations
Simulations of ultracold neutrons (UCN) using Kassiopeia, a particle tracking framework:
*https://github.com/KATRIN-Experiment/Kassiopeia*.
Fork of the modified Kassiopeia: *https://github.com/Blawker/Kassiopeia*.

## First project: Beamline
- Initialize the geometry of a beamline structure for UCN.
- Adding surface reflection for stainless steel.
- Generate initial energy spectrum according to TRIGA neutrons distribution[[1](1)].
- Adding slits to simulation the junction between the different part that compose the beamline.
- Adding binary program to create and add output file into Root's histograms.
- Adding Shell Script to parallelized simulations[[2](2)].

## Second project: Moving Mirror
- Initialize the geometry of a piston structure for UCN.
- Modify the source code of Kassiopeia to implement :
  - Moving part : surfaces, spaces, assemblies.
  - Interaction of UCN on moving surfaces[[3](3)].
- To create the motion of a part :
  - Enter the line in a config_file.xml to configure the motion :
  ```xml
  <ksmotion_surface_translation name="motion_surface_translation"
    surfaces="world/piston/moving_mirror/#"
    theta="[theta_motion]"
    phi="[phi_motion]"
    value_formula="[equation_motion]"
    value_min="[time_start_motion]"
    value_max="[time_end_motion]"
  />
  ```
  - Add the line below in the `<ksgeo_space />` structure command to link the motion to the simulation. It is recommanded to place the line in the root of the structure often called `space_world`.
  ```xml
  <command parent="root_surface_motion" field="add_surface_motion" child="motion_surface_translation"/>
  ```

  - Then enter a moving interaction component that has the same motion has the surface. Here is an example of interaction of UCN with stainless steel :
  ```xml
  <ksint_moving_surface_UCN name="int_moving_surface_UCN"
    eta="2.e-4"
    alpha="5.e-6"
    real_optical_potential="2.08e-7"
    correlation_length="20.e-9"
    theta="[theta_motion]"
    phi="[phi_motion]"
    value_formula="[equation_motion]"
    value_min="[time_start_motion]"
    value_max="[time_end_motion]"
  />
  ```
  - Add the line below in the `<ksgeo_space />` structure command to link the interaction to the surface.
  ```xml
  <geo_surface name="moving_surface_reflection" surfaces="world/piston/moving_mirror/#">
    <command parent="root_surface_interaction" field="set_surface_interaction" child="int_moving_surface_UCN"/>
  </geo_surface>
  ```

  - It is recommended to use `<define />` input because there could be many components that may have the same motion :
  ```xml
    <!-- Equation of motion is a time-dependent position function -->
  <define name="equation_motion" value="0.05*x"/>
  <define name="time_start_motion" value="0."/> <!-- Time (s) -->
  <define name="time_end_motion" value="10."/> <!-- Time (s) -->
  <define name="theta_motion" value="90."/> <!-- Angle (°) -->
  <define name="phi_motion" value="180."/> <!-- Angle (°) -->
  ```
  
- A basic simulation configuration can be found in the fork folder called `PistonSimulation.xml` : https://github.com/Blawker/Kassiopeia/blob/master/Kassiopeia/XML/Examples/PistonSimulation.xml

- The following file gives an example of configuration with two independent moving part (piston + shutter):
https://github.com/Blawker/UCN-Simulations/blob/master/config/Piston/tSPECT_piston_shutter_TRIGA_auto.xml

### Bibliography
[1](1) [I. Altarev et al. Neutron velocity distribution from a superthermal solid 2H2 ultracold neutron source. The European Physical Journal A, 37: 9-14 July 2008.](1)

[2](2) [GNU Parallel, https://www.gnu.org/software/parallel/](2)

[3](3) [Z. Bogorad  Ultracold Neutron Storage Simulation Using the Kassiopeia Software Package. Massachusetts Institute of Technology 2019, June 2019.](3)
