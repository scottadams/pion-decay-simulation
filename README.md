pion-decay-simulation
=====================

The simulation of a physics experiment in which pions decay into positrons through one of two different paths.

The outputs of the document including data for detected Muons and Positrons and the calculated acceptance, impurity and efficiency values can be found in the following location:

/pion-decay-simulation/Pion\ Decay Project/Derived\ Data/Pion\ Decay\ Project/Build/Products/Debug



Explanation:
A positively charged pion will either decay into a positron and a neutrino, or a muon, and a neutrino. The instability of the muon causes it to undergo further decay to a positron, resulting in their being 2 different paths for a pion to decay to a positron. This was simulated by generating arrays of 1000 positrons from pion decay, and 1000 from muon decay. The values of momenta of these particles were generated randomly in directions of incidence of theta and phi. The acceptance of the detector was set to only detect particles between angles of theta of 40¡ and 140¡, recording kinetic energy of 0 for all outside this range.  To create a more realistic simulation, the program was altered to smear recorded energies using a Gaussian distribution to simulate noise. The efficiency was defined as the number of events detected within the pure range per the total number of occurrences of that event, meaning that the detector is limited the range of the acceptance. Also, there is contribution to lack of efficiency from a slight impurity of positrons from pions, calculated within the code.