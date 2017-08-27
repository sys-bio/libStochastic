
from stBindings import *
import pylab
import numpy as np


gl = Stochastic ()

x1 = gl.addSpecies ('X1', 250, False)
x2 = gl.addSpecies ('X2', 0, True)
x3 = gl.addSpecies ('X3', 0, True)
x4 = gl.addSpecies ('X4', 0, False)

rxa1 = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa1, x2, 1)

rxa2 = gl.addFirstOrderReaction (x2, 0.65)
gl.addProduct (rxa2, x3, 1)

rxa3 = gl.addFirstOrderReaction (x3, 0.2)
gl.addProduct (rxa3, x4, 1)

#r = gl.setSeedUsingTime()
gl.setSeed (1503793684)

pylab.figure(figsize=(8,5)) 
pylab.xlim((0, 200))

m1 = gl.executeOnGrid (0, 100, 100)
gl.setRateConstant (rxa1, 0.2)
m2 = gl.executeOnGrid (100, 200, 100)  
 
m3 = np.vstack ((m1, m2))

pylab.plot (m3[:,0], m3[:,1], color='r', label='$x_2$')
pylab.plot (m3[:,0], m3[:,2], color='b', label='$x_3$')

pylab.xlabel ('Time')
pylab.legend()
pylab.savefig ('eventExample.pdf')

gl.free()

