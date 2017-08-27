

from stBindings import *
import pylab


gl = Stochastic ()

x1 = gl.addSpecies ('X1', 80, True)
x2 = gl.addSpecies ('X2', 0, True)

rxa = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa, x2, 1)

rxa = gl.addFirstOrderReaction (x2, 0.3)
gl.addProduct (rxa, x1, 1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

m = gl.execute (0, 100)
pylab.plot (m[:,0], m[:,1], color='r')
pylab.plot (m[:,0], m[:,2], color='b')
pylab.savefig ('equilibration.pdf')
gl.free()