#!/usr/bin/env python

import os
import argparse
import xml.etree.ElementTree as et

from array import array
from ROOT import TCanvas, TGraph, TMultiGraph, TLegend

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
parser.add_argument('--plot', action='store_true', help="Plot results")

parser.add_argument('--project', type=str, default='InheritanceTest',
                    help="Project name")
parser.add_argument('--top_func', type=str, default='InheritanceTest',
                    help="Top function name")
parser.add_argument('--source_dir', type=str,
                    help="Directory containing source files")
parser.add_argument('--fpga', type=str, default="xcku115-flvb2104-2-e")

args = parser.parse_args()

def ParseSynthReportXML(reportfile):
    assert('.xml' in reportfile)
    tree = et.parse(reportfile)
    root = tree.getroot()

    # resource
    nFF=int(root.find('AreaEstimates').find('Resources').find('FF').text)
    nLUT=int(root.find('AreaEstimates').find('Resources').find('LUT').text)
    
    # timing
    clk_est=float(root.find('PerformanceEstimates').find('SummaryOfTimingAnalysis').find('EstimatedClockPeriod').text)
    clk_set=float(root.find('UserAssignments').find('TargetClockPeriod').text)
    clk_unc=float(root.find('UserAssignments').find('ClockUncertainty').text)

    # latency
    #latency=int(root.find('PerformanceEstimates').find('SummaryOfOverallLatency').find('Interval-max').text)
    
    return nFF, nLUT, clk_est, clk_set, clk_unc

    
def ParseImplReportXML(reportfile):
    assert('.xml' in reportfile)
    tree = et.parse(reportfile)
    root = tree.getroot()

    # resource
    nFF=int(root.find('AreaReport').find('Resources').find('FF').text)
    nLUT=int(root.find('AreaReport').find('Resources').find('LUT').text)

    # timing
    clk_ach=float(root.find('TimingReport').find('AchievedClockPeriod').text)
    clk_set=float(root.find('TimingReport').find('TargetClockPeriod').text)

    return nFF, nLUT, clk_ach, clk_set

###########
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

###########
# container for performance analysis
TestPerf = {}
    
###########
# start all the tests    
for test in args.tests:
    print "Run test:", test

    # container for performance analysis
    test_perf_dict = {'nFF_syn':array('f'), 'nLUT_syn':array('f'),
                      'nFF_impl':array('f'), 'nLUT_impl':array('f'),
                      'CLK_syn':array('f'), 'CLK_impl':array('f'),
                      'CLK_set':array('f')}

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

        if (args.csim or args.csynth or args.cosim or args.impl):
            # write tcl script
            tclname=args.outdir.rstrip('/')+'/script_'+test+'_'+str(clk)+'ns.tcl'
            open(tclname,'wt').write(script_tmpl % vd)
        
            # run vivado_hls
            logfile=args.outdir.rstrip('/')+'/'+solution.replace('solution_','')+'.log'
            os.system('vivado_hls -f '+tclname+' | tee '+logfile)

        if args.plot:
            # Synthesis report
            synrpt = args.project+'/'+solution+'/syn/report/csynth.xml'
            # check if there is a report file
            if not os.path.exists(synrpt):
                print "WARNING: Cannot find synthesis report", synrpt
                continue
            
            nff_syn, nlut_syn, clk_syn, clk_set, clk_unc = ParseSynthReportXML(synrpt)
            assert(clk_set==float(clk)) # double check it's the right report
            test_perf_dict['nFF_syn'].append(nff_syn)
            test_perf_dict['nLUT_syn'].append(nlut_syn)
            test_perf_dict['CLK_syn'].append(clk_syn)
            test_perf_dict['CLK_set'].append(clk_set)
            
            # Implementation report
            implrpt = args.project+'/'+solution+'/impl/report/verilog/'+args.top_func+'_export.xml'
            # check if there is a report file
            if not os.path.exists(implrpt):
                print "WARNING: Cannot find implementation report", implrpt
                continue

            nff_imp, nlut_imp, clk_imp, clk_set = ParseImplReportXML(implrpt)
            assert(clk_set==float(clk)) # double check it's the right report
            test_perf_dict['nFF_impl'].append(nff_imp)
            test_perf_dict['nLUT_impl'].append(nlut_imp)
            test_perf_dict['CLK_impl'].append(clk_imp)

    # Add the results to the global dictionary for plotting
    TestPerf[test] = test_perf_dict

# plot
if args.plot:
    #print TestPerf
    
###########
    def PlotResults(npoints, xvar, yvar, title, xtitle, ytitle, outname):
        canvas = TCanvas()

        mg = TMultiGraph()
        leg = TLegend(0.7, 0.73, 0.9, 0.9)

        ymax = 0
        ymin = 999999999999999
        
        for it, test in enumerate(args.tests):
            xarray = TestPerf[test][xvar]
            yarray = TestPerf[test][yvar]
            gr = TGraph(npoints, xarray, yarray)
            gr.SetLineColor(it+2)
            gr.SetMarkerColor(it+2)
            gr.SetMarkerStyle(20+it)
            gr.SetMarkerSize(0.75)

            mg.Add(gr)
            leg.AddEntry(gr, test, "l")

            ymax = max(ymax, max(yarray)*1.05)
            ymin = min(ymin, min(yarray)*0.95)

        mg.Draw("APL")
        mg.SetTitle(title)
        mg.GetXaxis().SetTitle(xtitle)
        mg.GetYaxis().SetTitle(ytitle)
        mg.SetMaximum(ymax)
        mg.SetMinimum(ymin)

        leg.Draw("same")

        canvas.SaveAs(outname)
###########

    nclks = len(args.clocks)

    # post synthesis results
    PlotResults(nclks, 'nFF_syn', 'nLUT_syn', "Post synthesis resource usage",
                "number of FFs", "number of LUTs",
                "postsyn_resource.pdf")

    PlotResults(nclks, 'CLK_set', 'CLK_syn', "Post synthesis timing",
                "Target clock period (ns)", "Estimated clock period (ns)",
                "postsyn_timing.pdf")

    PlotResults(nclks, 'CLK_set', 'nFF_syn', "Post synthesis FFs",
                "Target clock period (ns)", "number of FFs",
                "postsyn_nff.pdf")

    PlotResults(nclks, 'CLK_set', 'nLUT_syn', "Post synthesis LUTs",
                "Target clock period (ns)", "number of LUTs",
                "postsyn_nlut.pdf")

    # post implementation results
    PlotResults(nclks, 'nFF_impl', 'nLUT_impl',
                "Post implementation resource usage",
                "number of FFs", "number of LUTs",
                "postimpl_resource.pdf")
    
    PlotResults(nclks, 'CLK_set', 'CLK_impl', "Post implementation timing",
                "Target clock period (ns)", "Achieved clock period (ns)",
                "postimpl_timing.pdf")

    PlotResults(nclks, 'CLK_set', 'nFF_impl', "Post implementation FFs",
                "Target clock period (ns)", "number of FFs",
                "postimpl_nff.pdf")

    PlotResults(nclks, 'CLK_set', 'nLUT_impl', "Post implementation LUTs",
                "Target clock period (ns)", "number of LUTs",
                "postimpl_nlut.pdf")
