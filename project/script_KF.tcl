############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################

# DO NOT USE HLS 2018.2, AS IT FAILS TO MEET TIMING. USE 2018.1 INSTEAD

# Delete project so as to reset it.
delete_project HLS_KF
# Create/open project
open_project HLS_KF

set SRCDIR ../TrackletAlgorithm/KF

# N.B. The c++11 flag is only available in Vivado HLS 2018.2 or later.
set CFLAGS "-std=c++11 -I$SRCDIR"
#set CFLAGS "-std=c++0x -I$SRCDIR"

puts "FUCK"
puts $CFLAGS
puts "SHIT"
set_top kalmanNode_top
add_files $SRCDIR/KalmanNode_top.h       -cflags $CFLAGS
add_files $SRCDIR/KalmanNode_top.cc      -cflags $CFLAGS
add_files $SRCDIR/KalmanNode.h           -cflags $CFLAGS
add_files $SRCDIR/KalmanNode.cc          -cflags $CFLAGS
add_files $SRCDIR/InputLinkFormatter.h   -cflags $CFLAGS
add_files $SRCDIR/InputLinkFormatter.cc  -cflags $CFLAGS
add_files $SRCDIR/OutputLinkFormatter.h  -cflags $CFLAGS
add_files $SRCDIR/OutputLinkFormatter.cc -cflags $CFLAGS
add_files $SRCDIR/ProtoStateCreator.h    -cflags $CFLAGS
add_files $SRCDIR/ProtoStateCreator.cc   -cflags $CFLAGS
add_files $SRCDIR/StateStubAssociator.h  -cflags $CFLAGS
add_files $SRCDIR/StateStubAssociator.cc -cflags $CFLAGS
add_files $SRCDIR/StubRams.h             -cflags $CFLAGS
add_files $SRCDIR/StubRams.cc            -cflags $CFLAGS
add_files $SRCDIR/KFstateRams.h          -cflags $CFLAGS
add_files $SRCDIR/KFstateRams.cc         -cflags $CFLAGS

add_files $SRCDIR/KalmanUpdate_dummy.h   -cflags $CFLAGS
add_files $SRCDIR/KalmanUpdate_dummy.cc  -cflags $CFLAGS

add_files $SRCDIR/KFstub.h                -cflags $CFLAGS
add_files $SRCDIR/KFstate.h               -cflags $CFLAGS
add_files $SRCDIR/HLSutilities.h          -cflags $CFLAGS
add_files $SRCDIR/HLSutilities.cc         -cflags $CFLAGS
add_files $SRCDIR/KFconstants.h           -cflags $CFLAGS
add_files $SRCDIR/KFpragmaOpts.h          -cflags $CFLAGS

#add_files $SRCDIR/KalmanUpdate.h         -cflags $CFLAGS
#add_files $SRCDIR/KalmanUpdate.cc        -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices.h       -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices.cc      -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices4.h      -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices4.cc     -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices5.h      -cflags $CFLAGS
#add_files $SRCDIR/KalmanMatrices5.cc     -cflags $CFLAGS

add_files -tb ../TestBenches/KF_test.cpp           -cflags $CFLAGS
#
set solution solution1
delete_solution $solution 
open_solution   $solution
# Virtex7 FPGA
#set_part {xc7vx690tffg1927-3} -tool vivado
# Kintex Ultrascale FPGA
# Used this until now
#set_part {xcku115-flvd1517-2-i} -tool vivado
set_part {xcku115-flvb1760-2-e} -tool vivado
#set_part {xcku115-flvd1517-3-e} -tool vivado
# Virtex Ultrascale-Plus FPGA
#set_part {xcvu9p-flgb2104-2-e} -tool vivado
#
#create_clock -period 240MHz -name default
#create_clock -period 280MHz -name default
create_clock -period 320MHz -name default
#create_clock -period 360MHz -name default
#create_clock -period 420MHz -name default
#create_clock -period 440MHz -name default
#create_clock -period 480MHz -name default
#
# Change safety margin to meet timing. Has no effect?
#set_clock_uncertainty 12.5%
#
# Encourage HLS to make more effort to find best solution.
config_bind -effort high
config_schedule -effort high -relax_ii_for_timing=0 -verbose
# Allow partitioning of arrays to improve pipelining.
config_array_partition -auto_partition_threshold 16 -auto_promotion_threshold 64 -include_ports -maximum_size 1024 -throughput_driven
# Allow HLS to use longer names in resource/latency usage profiles.
config_compile -name_max_length 100
# Remove variables from top-level interface if they are never used.
config_interface -trim_dangling_port
#
# Add HLS directives
#source "vivado_hls_directives.tcl"
#
# Compile & create IP Core
csim_design -clean -compiler gcc -mflags "-j8"
csynth_design
# Comment out the next 2 lines to speed things up if you are just optimising code.
#cosim_design -compiler gcc -trace_level port -rtl vhdl
# Adding "-flow impl" to this causes full Vivado implementation to be run, providing accurate resource use numbers (very slow).
#export_design -rtl vhdl -format ip_catalog
#export_design -flow impl -rtl vhdl -format ip_catalog
#
puts "Synthesis timing & utilization report in HLS_KF/$solution/syn/report/kalmanNode_top_csynth.rpt"
exit
