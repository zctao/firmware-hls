open_project -reset MergerTest
set_top MergerTest
add_files MergerTest/MergerTest.cpp
add_files -tb MergerTest/MergerTest_tb.cpp
open_solution -reset "solution1"
set_part {xcku115-flvb2104-2-e} -tool vivado
create_clock -period 4 -name default
