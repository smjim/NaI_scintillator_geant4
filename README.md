# Tutorial with "Physics Matters" youtube channel
1. initialize Geant4	(DONE)
2. define detector geometry	(DONE)
3. define physics list (without this, Geant would not know how a particle is supposed to interact with the geometry)	(DONE)
	3.5 tell geant to display	(DONE)
4. action initialization = takes care of computation/ multithreading	(DONE)
	add particle gun	(DONE)
5. visualization	(DONE)
6. detector volume	(DONE)
7. inserting sensitive detectors(?)
	adding radioactive decay
8. saving data to ROOT file
9. macro automizations
...
14. simulating radioactive decays and energy

# Real tasks for Geant4 after learning
1. create simulation of NaI scintillator coupled to pmt, with 137Cs source from different positions
	- how best to visualize the simulation to answer questions
2. simulation of neutron kinematics with wilson cone(?) vs other UCN beam couplers
	- which cone design is best (compare cone designs by throughput(?) or other metric, use identical UCN beam input)

## Learning requirements
- Basics of running Geant, visualization
- Saving data from Geant
- Radioactive source modeling
- Scintillation modeling
- PMT modeling(?)

# TODO: june 16 week
- continue on tutorial 7
