# firmware-hls
HLS implementation of the tracklet firmware

This repository is for studies of the C/C++ implementation for firmware using Vivado HLS. 

Source code goes in TrackletAlgorithm/, configuration/steering files go in project/; test bench code goes in ... TestBench. Memory printouts from emulation are in emData/.

A project can be generated by running tcl file with Vivado HLS in firmware-hls/project/ directory. One example project for testing ProjectionRouter:

	vivado_hls -f script_PR.tcl

It would create a project directory \<project> ("projrouter" in case of the above example). The project name is defined in the tcl script. To open the project in GUI:

	vivado_hls -p <project>


This is intended to be the HLS implementation of this repository:
https://github.com/cms-tracklet/fpga_emulation_longVM/tree/fw_synch, specifically this tag:
https://github.com/cms-tracklet/fpga_emulation_longVM/tree/ZT_181203

This is the fw_synch branch. See readme in that area. The emulation repository is dependent on imath, which should be checked out with this tag:
https://github.com/cms-tracklet/imath/tree/AH_181201

The correct versions of imath and fpga_emulation_longVM can be checked out and built with the following commands:

	git clone https://github.com/cms-tracklet/imath.git
	git clone https://github.com/cms-tracklet/fpga_emulation_longVM.git
	cd imath/
	git checkout AH_181201
	make -j5
	cd ../fpga_emulation_longVM/
	git checkout ZT_181203
	make fpga
