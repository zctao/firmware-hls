open_project -reset InheritanceTest
set_top InheritanceTest
add_files InheritanceTest/InheritanceTest.cc
add_files -tb InheritanceTest/InheritanceTest_tb.cc
open_solution -reset "solution1"
set_part {xcku115-flvb2104-2-e} -tool vivado
create_clock -period 4 -name default
#source "./InheritanceTest/solution1/directives.tcl"
#csim_design -compiler gcc
#csynth_design
#cosim_design
#export_design -rtl verilog -format syn_dcp

#exit
