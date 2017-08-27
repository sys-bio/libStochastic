# libStochastic
A portable C based library that implements the Gillespie direct method. 

A common approach to simulating chemical reaction systems is to formulate the problem as a set of ordinary differential equation and solve them using standard numerical procedures. Such a formulation works well when the number of molecules involved in the simulation is large and assumes a deterministic formulation for the underling chemical kinetics. However for systems such as gene regulatory networks where the number of molecules of a specific species can be of the order of 10s of molecules, the deterministic approach fails to capture important dynamical features. At low molecular numbers stochastic events dominate the dynamics. As a result much research has been devoted to developing numerical algorithms for computing the stochastic trajectories. One of the most common approaches is based on Gillespie's stochastic simulation algorithm, for example the direct method. Due to its simplicity the direct method has been implemented many times in software. However, unusually, there does not appear to be a C based reusable software library. This GitHub resource represents such a library

The current project can be compiled using Visual Solution 2017. The solution file is called StochasticSolution.sln

Two subprojects are in the solution:

1. A project ot create a DLL
2. A project to create a simple driver written in C

The python directory contains some examples, the ctypePython bindings and test code.

To use the bindings, copy libStochastic.dll to your python distribution (I uised Python 2.7). import sbBindings to access the library.

To run the tests, load testdsmts.py and run it. This test requires the expected outcome files (00001-results.csv, etc) to be in the same directory as testdsmts.py 
