#!/usr/bin/env python

import sys
#from os import path, mkdir
#import shutil
#from glob import glob
import numpy as np

if __name__ == "__main__":
	data = np.loadtxt(sys.argv[1], usecols=(4,6,7))
	data = (data[data[:,1].argsort()])[::-1]
	nev = len(data[:,0])
	#centralities = np.concatenate((np.linspace(0.1,1,10),np.linspace(2,100,99)))
	centralities = np.concatenate((np.linspace(0.001,0.01,10), np.linspace(0.02,0.1,9), np.linspace(0.2,1,9),np.linspace(2,100,99)))
	percents = 100.0-centralities
	#percentiles = asarray([percentile(data[:,1], pc) for pc in percents])
	#print centralities
	#print percentiles
	#print data[(nev*1.e-2*percents-1).astype(int),1]
	splitIndices = (((nev*1.e-2*centralities-1.0)[:-1]).astype(int)).tolist()
	percentileBins = np.array_split(data,splitIndices)
	#print splitIndices
	#sys.exit()
	#print percentileBins[-1]
	#centralities = append(centralities, 100.0)
	#print len(percentileBins), len(centralities), len(percents)
	print '#centrality dS/dy Npart_min Npart_max b_min(fm) b_max(fm)'
	print 0.0, 1.0e+06, 500.0, 500.0, 0.0, 0.0

	lastpcBin = np.array([[500.0, 1.0e+06, 0.0]])
	
	for ipcBin in xrange(len(percentileBins)):
		pcBin = percentileBins[ipcBin]
		'''print centralities[ipcBin],\
			min(pcBin[:,1]), max(pcBin[:,1]),\
			min(pcBin[:,0]), max(pcBin[:,0]),\
			min(pcBin[:,2]), max(pcBin[:,2])'''
		'''print centralities[ipcBin],\
			min(pcBin[:,1]), min(lastpcBin[:,1]),\
			min(pcBin[:,0]), max(pcBin[:,0]),\
			min(pcBin[:,2]), max(pcBin[:,2])'''
                print centralities[ipcBin],\
                        min(pcBin[:,1]),\
                        min(pcBin[:,0]), max(pcBin[:,0]),\
                        min(pcBin[:,2]), max(pcBin[:,2])
		lastpcBin = pcBin

