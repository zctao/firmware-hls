open_project -reset prmemctest
set_top PRMEMCTest
add_files ../TrackletAlgorithm/PRMEMCTest.cpp -cflags "-std=c++11"
add_files ../TrackletAlgorithm/TrackletCalculator.cpp -cflags "-std=c++11"
add_files ../TrackletAlgorithm/TC_L1L2.cpp -cflags "-std=c++11"
add_files -tb ../TestBenches/PRMEMCTest_test.cpp -cflags "-I../TrackletAlgorithm -std=c++11"
add_files -tb ../emData/PRMEMCTest
open_solution -reset "solution1"
set_part {xcvu7p-flvb2104-2-e} -tool vivado
create_clock -period 4 -name default
#csim_design
#csynth_design
#cosim_design
#export_design -rtl verilog -format ip_catalog

#exit