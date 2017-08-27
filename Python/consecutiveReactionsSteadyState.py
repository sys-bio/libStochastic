from stBindings import *
import pylab


gl = Stochastic ()

x1 = gl.addSpecies ('X1', 80, False)
x2 = gl.addSpecies ('X2', 0, True)
x3 = gl.addSpecies ('X3', 0, True)
x4 = gl.addSpecies ('X4', 0, False)

rxa = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa, x2, 1)

rxa = gl.addFirstOrderReaction (x2, 0.65)
gl.addProduct (rxa, x3, 1)

rxa = gl.addFirstOrderReaction (x3, 0.2)
gl.addProduct (rxa, x4, 1)


numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

pylab.figure(figsize=(8,5)) 
pylab.xlim((0, 70))
for i in range (60):
   gl.reset()
   m = gl.execute (0, 70)
   pylab.plot (m[:,0], m[:,1], color='r', alpha=0.2)
   pylab.plot (m[:,0], m[:,2], color='b', alpha=0.2)

pylab.xlabel ('Time')
pylab.savefig ('ThreeReactionsSteadyState.pdf')

gl.free()
