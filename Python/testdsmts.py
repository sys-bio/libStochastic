
from stBindings import *

import runStochSim

# DSMTS Test Suite

print "Starting test...."

sizeOfEnsemble = 10000

# dsmts-001-01
# ------------------------------
gl = Stochastic ()

x1 = gl.addSpecies ('X1', 100, True)

rxa = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa, x1, 2)

rxa = gl.addFirstOrderReaction (x1, 0.11)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00001', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-001-02
# ------------------------------
# This is an SBML test so not applicable


# dsmts-001-03
# ------------------------------
print "Note: StdDev test EXPECTED TO FAIL"
gl = Stochastic ()

x1 = gl.addSpecies ('X1', 100, True)

rxa = gl.addFirstOrderReaction (x1, 1.0)
gl.addProduct (rxa, x1, 2)

rxa = gl.addFirstOrderReaction (x1, 1.1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00003', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()

# dsmts-001-04
# ------------------------------
gl = Stochastic ()

x1 = gl.addSpecies ('X1', 10, True)

rxa = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa, x1, 2)

rxa = gl.addFirstOrderReaction (x1, 0.11)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00004', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()

#
# dsmts-001-05
# ------------------------------
gl = Stochastic ()

x1 = gl.addSpecies ('X1', 10000, True)

rxa = gl.addFirstOrderReaction (x1, 1.0)
gl.addProduct (rxa, x1, 2)

rxa = gl.addFirstOrderReaction (x1, 1.1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00005', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()

#
# dsmts-001-06
# ------------------------------
# Not applicable, added a boundary node and computes means and sd for that (which is zero)


# dsmts-001-07
# ------------------------------
gl = Stochastic ()

x1 = gl.addSpecies ('X1', 100, True)
sink = gl.addSpecies ('sink', 0, True)

rxa = gl.addFirstOrderReaction (x1, 0.1)
gl.addProduct (rxa, x1, 2)

rxa = gl.addFirstOrderReaction (x1, 0.11)
gl.addProduct (rxa, sink, 1)

numberOfVariables = 2
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00007', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-001-08
# ------------------------------
# Not applicable, SBML specific test

# dsmts-001-09
# ------------------------------
# Not applicable, SBML specific test

# dsmts-001-010
# ------------------------------
# Not applicable, SBML specific test

# dsmts-001-011
# ------------------------------
# Not applicable, SBML specific test

# dsmts-001-012
# ------------------------------
# Not applicable, SBML specific test

# dsmts-001-013
# ------------------------------
# Not applicable, libGillespie doesn't currently support arbitrary math expressions

# dsmts-001-014
# ------------------------------
# Not applicable, libGillespie doesn't currently support arbitrary math expressions

# dsmts-001-015
# ------------------------------
# Not applicable, libGillespie doesn't  support arbitrary math expressions

# dsmts-001-016
# ------------------------------
# Not applicable, libGillespie doesn't currently support arbitrary math expressions

# dsmts-001-017
# ------------------------------
# Not applicable, SBML test

# dsmts-001-018
# ------------------------------
# Not applicable,libGillespie doesn't currently support non-unit volumes

# dsmts-001-019
# ------------------------------
# Not applicable,libGillespie doesn't currently support assignment rules

# dsmts-002-01-20
# ------------------------------
gl = Stochastic ()

x = gl.addSpecies ('x', 0, True)
rxa = gl.addZeroOrderReaction (1.0)
gl.addProduct (rxa, x, 1)

rxa = gl.addFirstOrderReaction (x, 0.1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00020', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-002-01-21
# ------------------------------
gl = Stochastic ()

x = gl.addSpecies ('x', 0, True)
rxa = gl.addZeroOrderReaction (10.0)
gl.addProduct (rxa, x, 1)

rxa = gl.addFirstOrderReaction (x, 0.1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00021', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-002-01-22
# ------------------------------
# Not applicable This is a specific SBML test

# dsmts-002-01-23
# ------------------------------
gl = Stochastic ()

x = gl.addSpecies ('x', 0, True)
rxa = gl.addZeroOrderReaction (1000.0)
gl.addProduct (rxa, x, 1)

rxa = gl.addFirstOrderReaction (x, 0.1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00023', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-002-01-24
# ------------------------------
gl = Stochastic ()

x = gl.addSpecies ('x', 0, True)
source = gl.addSpecies ('source', 0, False)
sink = gl.addSpecies ('sink', 0, False)

rxn = gl.addZeroOrderReaction (10.0)
gl.addProduct (rxn, x, 1)

rxn = gl.addFirstOrderReaction (x, 0.1)
gl.addProduct (rxn, sink, 1)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00024', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-002-01-25
# ------------------------------
# Not applicable because boundary species cannot be written to the output results

# dsmts-002-01-26
# ------------------------------
# Not applicable because boundary species cannot be written to the output results

# dsmts-002-01-27
# ------------------------------
# Not applicable, this is a SBML test 

# dsmts-002-01-28
# ------------------------------
# Not applicable, this is a SBML test 

# dsmts-002-01-28
# ------------------------------
# Event test, can be implemented using multiple executeToGrid calls

# dsmts-002-01-29
# ------------------------------
# Event test, can be implemented using multiple executeToGrid calls

# dsmts-003-01-30
# ------------------------------
gl = Stochastic ()

P  = gl.addSpecies ('P', 100, True)
P2 = gl.addSpecies ('P2', 0, True)

rxa = gl.addSecondOrderReaction (P, 0.001)
gl.addProduct (rxa, P2, 1)

rxa = gl.addFirstOrderReaction (P2, 0.01)
gl.addProduct (rxa, P, 2)

numberOfVariables = 2
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00030', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-003-01-31
# ------------------------------
gl = Stochastic ()

P  = gl.addSpecies ('P', 1000, True)
P2 = gl.addSpecies ('P2', 0, True)

rxa = gl.addSecondOrderReaction (P, 0.0002)
gl.addProduct (rxa, P2, 1)

rxa = gl.addFirstOrderReaction (P2, 0.004)
gl.addProduct (rxa, P, 2)

numberOfVariables = 2
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00031', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()

# dsmts-003-01-32
# ------------------------------
# This is an event test, can be implemented using a sequence of executeToGrid calls

# dsmts-003-01-33
# ------------------------------
# This is an event test, can be implemented using a sequence of executeToGrid calls

# dsmts-003-01-34
# ------------------------------
# Not appicable, libGillespie does nopt support arbitrary rate expressions. 

# dsmts-003-01-35
# ------------------------------
# Not appicable, libGillespie does nopt support arbitrary rate expressions. 

# dsmts-003-01-36
# ------------------------------
# Not appicable, libGillespie does nopt support arbitrary rate expressions. 


# dsmts-003-01-37
# ------------------------------
gl = Stochastic ()

x  = gl.addSpecies ('x', 0, True)

rxa = gl.addZeroOrderReaction (1.0)
gl.addProduct (rxa, x, 5)

gl.addFirstOrderReaction (x, 0.2)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00037', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-003-01-38
# ------------------------------
gl = Stochastic ()

x  = gl.addSpecies ('x', 0, True)

rxa = gl.addZeroOrderReaction (1.0)
gl.addProduct (rxa, x, 10)

gl.addFirstOrderReaction (x, 0.4)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00038', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()


# dsmts-003-01-39
# ------------------------------
gl = Stochastic ()

x  = gl.addSpecies ('x', 0, True)

rxa = gl.addZeroOrderReaction (1.0)
gl.addProduct (rxa, x, 100)

gl.addFirstOrderReaction (x, 4.0)

numberOfVariables = 1
numberOfPoints = 51
timeEnd = 50

testFlags = runStochSim.runStochTest(gl, '00039', timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables)
runStochSim.printOutTestFail (testFlags)

gl.free()













