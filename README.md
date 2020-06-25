# UCN-Simulations
Simulations of ultracold neutrons (UCN) using Kassiopeia, a particle tracking framework:
*https://github.com/KATRIN-Experiment/Kassiopeia*.

## First project: Beamline
- Initialize the geometry of a beamline structure for UCN.
- Adding surface reflection for stainless steel.
- Generate initial energy spectrum according to TRIGA neutrons distribution[*](1).
- Adding binary program to create and add output file into Root's histograms.
- Adding Shell script to merge Root histograms and automate simulations and output writing.

## Second project: Moving Mirror
- Initialize the geometry of a piston struture for UCN.
- Modify the source code of Kassiopeia to implement moving part and interaction of UCN on surfaces[*](2).

### Bibliography
[*](1) [I. Altarev et al. Neutron velocity distribution from a superthermal solid 2H2 ultracold neutron source. The European Physical Journal A, 37: 9-14 July 2008.](1)

[*](2) [Z. Bogorad  Ultracold Neutron Storage Simulation Using the Kassiopeia Software Package. Massachusetts Institute of Technology 2019, June 2019.](2)
