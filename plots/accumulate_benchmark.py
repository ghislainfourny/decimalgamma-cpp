#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
from os.path import realpath, dirname, basename, join

# Determine names of output and input files
scriptname=realpath(__file__)
outputdir=join(dirname(scriptname), 'output')
outputname=join(outputdir, basename(scriptname)[:-3] + '.pdf')
inputdir=join(join(dirname(dirname(scriptname)), 'experiments'), 'output')
inputname=join(inputdir, basename(scriptname)[:-3] + '.csv')

# Read input
df = pd.read_csv(inputname, sep=';')

# Compute derived metrics
df['runtime_per_element'] = df['runtime'] / df['N']

# Create plot
fig = plt.figure()
ax = fig.add_subplot(111)
ax.set(xlabel='input size [#floats]', ylabel='runtime per element [ns]',
       title='Performance of T.operator+=(float)')
plt.xscale('log')
plt.yscale('log')
d = df[df['type'] == 'decimalinfinite']
plt.plot(d.N, d.runtime_per_element, label='decimalinfinite')
d = df[df['type'] == 'float']
plt.plot(d.N, d.runtime_per_element, label='float')
plt.legend()

# Save PDF
fig.savefig(outputname)
