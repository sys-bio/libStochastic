
import numpy as np
import math
import pylab

def printOutTestFail (testData):
    if testData[0] < 3:
       print "Mean Test Successful:  ", testData[0],
    else:
       print "Mean Test ****Fail!**** = ", testData[1],
    
    if testData[1] < 6:
       print "StdDev Test Successful:  ", testData[1]
    else:
       print "StdDev Test ****Fail!**** = ", testData[1]
    
    
def runStochTest(gl, nameOfExpectedData, timeEnd, sizeOfEnsemble, numberOfPoints, numberOfVariables):
       
   print "Starting test for: " + nameOfExpectedData,
   # Read in the expected mean/std dev data, ignore header
   csv = np.genfromtxt (nameOfExpectedData + '-results.csv', delimiter=',',skip_header=1)
   
   # Hack for model 00024, remove the boundary species columns
   if nameOfExpectedData == '00024':
       # Delete the boundary species column, last 2 cols and
       # cols 2, 3 (indexing from 0)
       #csv = np.delete (csv, np.s_[2,4], axis = 0)
       csv = np.delete (csv, 3, 1)
       csv = np.delete (csv, 2, 1)
       csv = np.delete (csv, 4, 1)
       csv = np.delete (csv, 3, 1)
       
   gl.setSeedUsingTime()

   M = np.zeros(shape=(numberOfPoints, numberOfVariables+1))
   S = np.zeros(shape=(numberOfPoints, numberOfVariables+1))
   
   # Mp holds the computed means from the 'previous' running mean
   # Needed for the std dev calculation
   Mp = gl.executeOnGrid(0.0, timeEnd, numberOfPoints)  
      
   for i in range (sizeOfEnsemble):
       gl.reset()
       data = gl.executeOnGrid(0.0, timeEnd, numberOfPoints)
       # Compute running mean and variance (Welford method)
       np.copyto (M, Mp + (data - Mp)/(i+2)) # Already done one, also i starts at 0 so add one
       np.copyto (S, S + (data - Mp)*(data - M))
       np.copyto (Mp, M)

   # Compute Variance
   S = S/(sizeOfEnsemble-1)

   # Compute standard deviation 
   S = np.sqrt(S)

   meanTestData = 0
   StdTestData = 0
   print "#nvars: ", numberOfVariables
   for col in range (numberOfVariables):
       
       indexOfStdColumn =  col+numberOfVariables+1
       
       computedMeanArray = M[1:,[col+1]]  # Don't want first row
       computedStdArray = S[1:,[col+1]]    # Don't want first row
       
       expectedMeanArray = csv[1:,[col+1]] # Don't want first row,
       expectedStdArray = csv[1:,[indexOfStdColumn]] # Don't want first row 
        
       # Compute the statistics for the mean data 
       f1 = np.divide ((computedMeanArray - expectedMeanArray), expectedStdArray)
       computedMeanStatistic = math.sqrt(sizeOfEnsemble)*f1 
     
       # Compute the statistics for the standard deviation data
       f1 = computedStdArray*computedStdArray
       f1 = np.divide (f1,(expectedStdArray*expectedStdArray)) - 1
       computedStdStatistic = math.sqrt(sizeOfEnsemble/2)*f1 
        
       # For debugging...
       #pylab.plot (computedMeanArray)
       #pylab.plot (expectedMeanArray)
       ##pylab.plot (expectedStdArray)
       #pylab.plot (computedSdArray)
         
       # Return true if it passes, false if not
       for i in range(numberOfPoints-1): # Remember we don't have the top row
           if (computedMeanStatistic[i] < -3) or (computedMeanStatistic[i] > 3):
               
               meanTestData = meanTestData + 1
               break
 
       for i in range(numberOfPoints-1): # Remember we don't have the top row
           if (computedStdStatistic[i] < -5) or (computedStdStatistic[i] > 5):
               StdTestData = StdTestData + 1
               break

   return (meanTestData, StdTestData)