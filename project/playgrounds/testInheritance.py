#!/usr/bin/env python

import os
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('tests', nargs='+', choices=['base','basev','derv1','derv2'],
                    default=['base','basev','derv1','derv2'],
                    help="Types of test to run")

parser.add_argument('-c', '--clocks', nargs='+', type=float, default = [4],
                    help="Clock periods in ns")
parser.add_argument('-o', '--outdir', type=str, default='./',
                    help="Output directory")

parser.add_argument('--csim', action='store_true', help="Run c simulation")
parser.add_argument('--csynth', action='store_true', help="Run synthesis")
parser.add_argument('--cosim', action='store_true', help="Run C/RTL co-simulation")
parser.add_argument('--impl', action='store_true', help="Run implementation")

parser.add_argument('--project', type=str, default='InheritanceTest',
                    help="Project name")
parser.add_argument('--top_func', type=str, default='InheritanceTest',
                    help="Top function name")
parser.add_argument('--source_dir', type=str,
                    help="Directory containing source files")
parser.add_argument('--fpga', type=str, default="xcku115-flvb2104-2-e")

#parser.add_argument('--plot')

args = parser.parse_args()

# vivado hls tcl script template
script_tmpl = '''open_project -reset %(projname)s
set_top %(topfunc)s
add_files -cflags "-std=c++11" %(sourcefile)s
add_files -cflags "-std=c++11" -tb %(testbench)s
open_solution -reset "%(sols)s"
set_part {%(fpga)s} -tool vivado
create_clock -period %(clk)s -name default
#csim_design
#csynth_design
#cosim_design
#export_design -rtl verilog -format syn_dcp
exit
'''

if args.csim:
    script_tmpl = script_tmpl.replace("#csim_design", "csim_design")
if args.csynth:
    script_tmpl = script_tmpl.replace("#csynth_design", "csynth_design")
if args.cosim:
    script_tmpl = script_tmpl.replace("#cosim_design", "cosim_design")
if args.impl:
    script_tmpl = script_tmpl.replace(
        "#export_design -rtl verilog -format syn_dcp",
        "export_design -rtl verilog -format syn_dcp")
    

for test in args.tests:
    print "Run test:", test

    srcdir = args.project if args.source_dir is None else args.source_dir.rstrip('/')
    srcfile = srcdir+'/'+'InheritanceTest_'+test+'.cc'
    tbfile = srcdir+'/'+'InheritanceTest_tb.cc'
    
    for clk in args.clocks:

        print 'clock period', clk, 'ns'
        
        solution = 'solution_'+test+'_'+str(clk)+'ns'
        
        vd = locals()
        vd['projname'] = args.project
        vd['topfunc'] = args.top_func
        vd['sourcefile'] = srcfile
        vd['testbench'] = tbfile
        vd['sols'] = solution
        vd['fpga'] = args.fpga
        vd['clk'] = str(clk)

        # write tcl script
        tclname = args.outdir.rstrip('/')+'/'+'script_'+test+'_'+str(clk)+'ns.tcl'
        open(tclname,'wt').write(script_tmpl % vd)
        
        # run vivado_hls
        logfile = args.outdir.rstrip('/')+'/'+solution.replace('solution_','')+'.log'
        os.system('vivado_hls -f '+tclname+' | tee '+logfile)

