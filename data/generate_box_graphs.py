#!/usr/bin/python
import matplotlib.pyplot as plt
from scipy.stats import *
import numpy as np
import os
import glob
import sys
import math

def clean_data(name):
	data = []
	
	for f in glob.glob(name):
		new_data = []
		with open(f) as infile:
			for line in infile:
				v = []
				values = line.split(', ')
				for value in values:
					d = unicode(value, 'utf-8')
					if d.isnumeric():
						v.append(float(d))

				new_data.append(v)
		data.append(new_data)
	return data

def find_avgs(data):
	avg_data = []

	for block in data:
		block_avg = []

		for trial in block:
			trial_avgs = []
			trial_avg = []

			for gen in trial:
				gen_avg = 0

				for ind in gen:
					gen_avg += ind

				gen_avg /= len(gen)
				trial_avg.append(gen_avg)

			trial_avgs.append(trial_avg)
		
		for i in range(0, len(trial_avgs[0])):
			trialwide_avg = 0
			
			for t in trial_avgs:
				trialwide_avg += t[i]
			
			trialwide_avg /= len(trial_avgs)
			block_avg.append(trialwide_avg)

		avg_data.append(block_avg)
	
	return avg_data

def plot_convergence(data, l1, l2, l3, title):
	g=range(1,101)

	diffs = []
	for block in data:
		trial_diff = []
		previous = 0

		for value in block:	
			trial_diff.append(math.sqrt((previous ** 2) + (value ** 2)))
			previous = value

		diffs.append(trial_diff)

	plt.subplot(211)
	plt.title(title)
	plt.plot(g, data[0], label=l1)
	plt.plot(g, data[1], label=l2)
	plt.plot(g, data[2], label=l3)
	plt.legend()
	plt.xlabel('Generation', fontsize=14)
	plt.ylabel('Average Fitness', fontsize=14)
	
	plt.subplot(212)
	plt.plot(g, diffs[0], label=l1) 
	plt.plot(g, diffs[1], label=l2)
	plt.plot(g, diffs[2], label=l3)
	plt.ylabel('Distance between Generations', fontsize=14)

	plt.show()

	return

def plot_box(data,l1,l2,l3,title):
	plt.figure()
	plt.title(title)
	plt.boxplot(data, labels={l1, l2, l3}, notch=False, sym='+', vert=True, whis=1.5, positions=None, widths=None, patch_artist=False, bootstrap=None, usermedians=None, conf_intervals=None)
	plt.show()
	
	p1 = ranksums(data[0], data[1])
	p2 = ranksums(data[0], data[2])
	p3 = ranksums(data[1], data[2])

	print p1
	print p2
	print p3

	return

def find_fit(data):
	return []

def main():
	data = []
	
	for i in range(1, 4):
		data.append(clean_data(sys.argv[i]))

	avg_data = find_avgs(data)
	most_fit = find_fit(data)

	plot_convergence(avg_data, sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
	plot_box(most_fit, sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[8])

if __name__ == "__main__":
	main()	
