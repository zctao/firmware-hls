############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project -reset sectproc
set_top SectorProcessor
add_files ../TrackletAlgorithm/SectorProcessor.cpp
add_files -tb ../TestBenches/SectorProcessor_test.cpp -cflags "-I../TrackletAlgorithm"
add_files -tb ../TestBenches/emData_PR
open_solution -reset "solution1"
set_part {xcku115-flvb2104-2-e} -tool vivado
create_clock -period 4 -name default
#source "./sectproc/solution1/directives.tcl"
#csim_design -compiler gcc
#csynth_design
#cosim_design
#export_design -rtl verilog -format syn_dcp

#exit
