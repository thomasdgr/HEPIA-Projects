import matplotlib.pyplot as plt
import numpy as np
import sys
import re

testsite_array = []
with open(sys.argv[1], "r") as a_file:
    testsite_array=[line.split(',') for line in a_file.readlines() if line.strip()]

print(testsite_array)

plt.rcdefaults()
fig, ax = plt.subplots()
nNeurons_nIterations = [(int(x[0]), int(x[1])) for x in testsite_array]
y_pos = np.arange(len(nNeurons_nIterations))
ax.barh(y_pos, [float(x[2]) for x in testsite_array], xerr=[float(x[3]) for x in testsite_array], align='center')
plt.yticks(y_pos, labels=nNeurons_nIterations)
ax.invert_yaxis()  # labels read top-to-bottom
ax.set_xlabel('Training rate')
ax.set_ylabel("nNeurons, nIterations")

ax.set_title('Training rates of Bagging in Australian Credit Approval data set')
plt.show()