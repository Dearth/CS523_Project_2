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

def plot_sc_convergence(data, l1, l2, l3, title):
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
	plt.plot(g, data[1], '-.', label=l2)
	plt.plot(g, data[2], '--', label=l3)
	plt.legend()
	plt.xlabel('Generation', fontsize=14)
	plt.ylabel('Average Fitness', fontsize=14)
	
	plt.subplot(212)
	plt.plot(g, diffs[0], label=l1) 
	plt.plot(g, diffs[1], '-.', label=l2)
	plt.plot(g, diffs[2], '--', label=l3)
	plt.ylabel('Distance between Generations', fontsize=14)

	plt.show()

	return

def plot_m_convergence(data, l1, l2, l3, l4, l5, title):
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
    plt.plot(g, data[1], '-.', label=l2)
    plt.plot(g, data[2], '--', label=l3)
    plt.plot(g, data[3], '.', label=l4)
    plt.plot(g, data[4], '.-', label=l5)
    plt.legend()
    plt.xlabel('Generation', fontsize=14)
    plt.ylabel('Average Fitness', fontsize=14)

    plt.subplot(212)
    plt.plot(g, diffs[0], label=l1)
    plt.plot(g, diffs[1], '-.', label=l2)
    plt.plot(g, diffs[2], '--', label=l3)
    plt.plot(g, diffs[3], '.', label=l4)
    plt.plot(g, diffs[4], '.-', label=l5)
    plt.ylabel('Distance between Generations', fontsize=14)

    plt.show()

    return

def plot_i_convergence(data, l1, l2, l3, l4, title):
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
    plt.plot(g, data[1], '-.', label=l2)
    plt.plot(g, data[2], '--', label=l3)
    plt.plot(g, data[3], '.', label=l4)
    plt.legend()
    plt.xlabel('Generation', fontsize=14)
    plt.ylabel('Average Fitness', fontsize=14)

    plt.subplot(212)
    plt.plot(g, diffs[0], label=l1)
    plt.plot(g, diffs[1], '-.', label=l2)
    plt.plot(g, diffs[2], '--', label=l3)
    plt.plot(g, diffs[3], '.', label=l4)
    plt.ylabel('Distance between Generations', fontsize=14)

    plt.show()

    return

def plot_e_convergence(data, l1, l2, title):
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
    plt.plot(g, data[1], '-.', label=l2)
    plt.legend()
    plt.xlabel('Generation', fontsize=14)
    plt.ylabel('Average Fitness', fontsize=14)

    plt.subplot(212)
    plt.plot(g, diffs[0], label=l1)
    plt.plot(g, diffs[1], '-.', label=l2)
    plt.ylabel('Distance between Generations', fontsize=14)

    plt.show()

    return

def plot_sc_box(data,l1,l2,l3,title):
	plt.figure()
	plt.title(title)
	plt.boxplot(data, labels={l1, l2, l3}, notch=False, sym='+', vert=True, whis=1.5, positions=None, widths=None, patch_artist=False, bootstrap=None, usermedians=None, conf_intervals=None)
	plt.ylabel('Fitness')
	plt.show()
	
	p1 = ranksums(data[0], data[1])
	p2 = ranksums(data[0], data[2])
	p3 = ranksums(data[1], data[2])

	print p1
	print p2
	print p3

	return

def plot_e_box(data,l1,l2,title):
    plt.figure()
    plt.title(title)
    plt.boxplot(data, labels={l1, l2}, notch=False, sym='+', vert=True, whis=1.5, positions=None, widths=None, patch_artist=False, bootstrap=None, usermedians=None, conf_intervals=None)
    plt.ylabel('Fitness')
    plt.show()

    p1 = ranksums(data[0], data[1])

    print p1

    return

def plot_m_box(data,l1,l2,l3,l4,l5,title):
    plt.figure()
    plt.title(title)
    plt.boxplot(data, labels={l1, l2, l3, l4, l5}, notch=False, sym='+', vert=True, whis=1.5, positions=None, widths=None, patch_artist=False, bootstrap=None, usermedians=None, conf_intervals=None)
    plt.ylabel('Fitness')
    plt.show()

    return

def plot_i_box(data,l1,l2,l3,l4,title):
    plt.figure()
    plt.title(title)
    plt.boxplot(data, labels={l1, l2, l3, l4}, notch=False, sym='+', vert=True, whis=1.5, positions=None, widths=None, patch_artist=False, bootstrap=None, usermedians=None, conf_intervals=None)
    plt.ylabel('Fitness')
    plt.show()

    return

def find_fit(data):
	fit = []

	for block in data:
		block_fit = []
		for trial in block:
			for gen in range(95, len(trial)):
				block_fit.append(trial[gen][-1]);

		fit.append(block_fit)

	return fit

def main():
	data = []
	max_range = 4	

	print len(sys.argv)

	if len(sys.argv) == 13:
		max_range = 6
	
	if len(sys.argv) == 7:
		max_range = 3

	if len(sys.argv) == 11:
		max_range = 5

	for i in range(1, max_range):
		data.append(clean_data(sys.argv[i]))

	avg_data = find_avgs(data)
	most_fit = find_fit(data)

	if len(data) == 3:
		plot_sc_convergence(avg_data, sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
		plot_sc_box(most_fit, sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[8])

	elif len(data) == 2:
		plot_e_convergence(avg_data, sys.argv[3], sys.argv[4], sys.argv[5])
		plot_e_box(most_fit, sys.argv[3], sys.argv[4], sys.argv[6])

	elif len(data) == 4:
		plot_i_convergence(avg_data, sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[9])
		plot_i_box(most_fit, sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[10])

	else:
		plot_m_convergence(avg_data, sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[9], sys.argv[10], sys.argv[11])
		plot_m_box(most_fit, sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[9], sys.argv[10], sys.argv[12])
		

if __name__ == "__main__":
	main()	
