# -*- coding: utf-8 -*-
"""
Created on Thu May 28 18:24:59 2015

@author: pietro
@website:http://pennestri.me
@mail:pietro.pennestri@gmail.com
"""

import matplotlib.pyplot as plt
import numpy as np
import math
from scipy.optimize import curve_fit
plt.close("all")

ydata = np.array([0.5,0.75,1.1,1.5,1.9])
xdata = np.array([2.92,3.15,3.29,3.5,3.81])
num_elements=len(xdata)

def func(x, a, b):
    return a*x+ b
#
# curve_fit: Math procedure of the scipy math library
# popt:
# Optimal values for the parameters so 
#that the sum of the squared error of 
# (func-ydata)^2 is minimized
# pcov:
# The diagonals of pcov provide the variance 
# of the parameter estimate

popt, pcov = curve_fit(func, xdata, ydata)
print popt

a=popt[0]
b=popt[1]

#error
k=0
s=0
for x in xdata:
    y=func(x,a,b)
    s=s+(y-ydata[k])**2
    k=k+1
s=math.sqrt(s/num_elements)    
print "Square root of sum of squares of residuals=",s

print '------'
print pcov
plt.figure()
plt.plot(xdata, ydata, 'ko', label="Original Data")
plt.plot(xdata, func(xdata, *popt), 'r-', label="Fitted Curve")
plt.xlabel('Arduino voltage (V)')
plt.ylabel('Alcohol concentration  (mg/l)')
#plt.xscale('log')#
#plt.yscale('log')#
plt.grid()
plt.show()