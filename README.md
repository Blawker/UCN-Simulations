# UCN-Simulations
Simulations of ultracold neutrons (UCN) using Kassiopeia, a particle tracking framework:
*https://github.com/KATRIN-Experiment/Kassiopeia*.
Fork of the modified Kassiopeia: *https://github.com/Blawker/Kassiopeia*.

## First project: Beamline
- Initialize the geometry of a beamline structure for UCN.
- Adding surface reflection for stainless steel.
- Generate initial energy spectrum according to TRIGA neutrons distribution[1](1).
- Adding binary program to create and add output file into Root's histograms.
- Adding Shell Script to parallelized simulations[2](2).

## Second project: Moving Mirror
- Initialize the geometry of a piston structure for UCN.
- Modify the source code of Kassiopeia to implement :
  - Moving part : surfaces, spaces, assemblies.
  - Interaction of UCN on moving surfaces[3](3).
- To create a motion of a part, enter the line in the config_file.xml :

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

It is preferable to use `<define />` input because there could be interaction that must have the same motion :
```xml
  <!-- Equation of motion is a time-dependent position function -->
<define name="equation_motion" value="0.05*x"/>
<define name="time_start_motion" value="0."/> <!-- Time (s) -->
<define name="time_end_motion" value="10."/> <!-- Time (s) -->
<define name="theta_motion" value="90."/> <!-- Angle (°) -->
<define name="phi_motion" value="180."/> <!-- Angle (°) -->
```

### Bibliography
[1](1) [I. Altarev et al. Neutron velocity distribution from a superthermal solid 2H2 ultracold neutron source. The European Physical Journal A, 37: 9-14 July 2008.](1)

[2](2) [https://www.gnu.org/software/parallel/](2)

[3](3) [Z. Bogorad  Ultracold Neutron Storage Simulation Using the Kassiopeia Software Package. Massachusetts Institute of Technology 2019, June 2019.](3)
