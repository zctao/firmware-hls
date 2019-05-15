open_project -reset connecttest
set_top topfunction
add_files topfunction.cc -cflags "-std=c++11"
add_files -tb topfunction_tb.cc -cflags "-std=c++11"
open_solution -reset "solution1"
set_part {xcvu7p-flvb2104-1-e} -tool vivado
create_clock -period 4 -name default
