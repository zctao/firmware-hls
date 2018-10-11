############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project -reset ConstructorTest
set_top ConstructorTest
add_files ConstructorTest/ConstructorTest.cc
add_files -tb ConstructorTest/ConstructorTest_tb.cc
open_solution -reset "solution1"
set_part {xcku115-flvb2104-2-e} -tool vivado
create_clock -period 10 -name default
#source "./ConstructorTest/solution1/directives.tcl"
csim_design -compiler gcc
csynth_design
cosim_design
export_design -rtl verilog -format syn_dcp

exit
