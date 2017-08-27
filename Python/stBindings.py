
# Very basic ctypes interface to libStochastic. 
# August 2017
# Pubic Domain

from ctypes import *
import numpy as np
np.set_printoptions(threshold=np.nan) # To display entire array at console

# Create an instance of the Stochastic object, returns handle to object
class Stochastic:
    
    def __init__(self):
        
        try:
          self.gl = cdll.LoadLibrary ("libStochastic.dll")
          

          self.gl.gl_getMatrixValue.argtypes = [c_int, c_int, c_int] 
          self.gl.gl_getMatrixValue.restype = c_double
          self.gl.gl_addUniUniReaction.argtypes = [c_int, c_int, c_int, c_double]
          self.gl.gl_addFirstOrderReaction.argtypes = [c_int, c_int, c_double]
          self.gl.gl_addSpecies.argtypes = [c_int, c_char_p, c_int, c_int]
          self.gl.gl_addSpecies.restype = c_int
          self.gl.gl_addProduct.argtypes = [c_int, c_int, c_int, c_int]
          self.gl.gl_addProduct.restype = c_int
   
          #self.gl.gl_setRateConstant.argtypes = [c_int, c_int, c_int]
 
          self.gl.gl_execute.argtypes = [c_int, c_double, c_double]
          self.gl.gl_executeOnGrid.argtypes = [c_int, c_double, c_double, c_int]
          self.gl.gl_getMatrixRows.argtypes = [c_int]
          self.gl.gl_moveOneStep.argtypes = [c_int, c_double]
          self.gl.gl_moveOneStep.restype = c_double
          self.gl.gl_setSeedUsingTime = c_int
          self.gl.gl_addZeroOrderReaction.argtypes = [c_int, c_double]
          self.gl.gl_addSecondOrderReaction.argtypes = [c_int, c_int, c_double]

          self.handle = self.gl.gl_createStochastic()
        except (AttributeError, OSError):
           pass
        
    # I am sure there is a better way but for now, user must explicitly free resources
    def free (self):       
        self.gl.gl_freeStochastic (self.handle)

    # Add a species to the model. Set isFloating to true if the species is expected
    # to change during the simulation. value is the initial number of molecules and
    # name is the name of the species. Returns the species index (see addReactant//addProduct)
    def addSpecies (self, name, amount, floating):
        return self.gl.gl_addSpecies (self.handle, name, amount, floating)
      
    # Create a new reaction that is zero order:  ->
    # Returns NULL if unsuccessful
    def addZeroOrderReaction (self, rateConstant):
        return self.gl.gl_addZeroOrderReaction (self.handle, rateConstant)
    
    # Create a new reaction that is first order: X ->
    # Returns NULL if unsuccessful
    def addFirstOrderReaction (self, speciesIndex, rateConstant):           
        return self.gl.gl_addFirstOrderReaction (self.handle, speciesIndex, rateConstant)
      
    # Add a product to the reaction given by the handle rxa.  speciesindex is the handle
    # returned by addSpecies. stoichiometry is the stoichimetric coefficient, always positive  
    # Returns -1 if unsuccessful
    # Any number of products can be added to a reaction
    def addProduct (self, reactionHandle, speciesIndex, stoichiometry):     
        self.gl.gl_addProduct (self.handle, reactionHandle, speciesIndex, stoichiometry)
       
    # Create a new reaction that is first order: X1 -> X2
    # Returns NULL if unsuccessful
    def addUniUniReaction (self, reactantIndex, productIndex, rateConstant):
          return self.gl.gl_addUniUniReaction (self.handle, reactantIndex, productIndex, rateConstant)
      
    # Create a new reaction that is second order: 2X ->
    # Returns NULL if unsuccessful
    def addSecondOrderReaction (self, speciesIndex, rateConstant): 
        return self.gl.gl_addSecondOrderReaction (self.handle, speciesIndex, rateConstant)
          
    # Set the value for the rate constant given the reaction handle rxa
    def setRateConstant (self, rxn, rateConstant):       
        self.gl.gl_setRateConstant (self.handle, rxn, rateConstant)
        
    def setAmount (self, speciesIndex, newAmount):
        return self.gl.gl.setAmount (self.handle, speciesIndex, newAmount)
    
    # Run a Gillespie simulation, starting at timeStart and ending at timeEnd.
    def execute (self, startTime, endTime):      
        m = self.gl.gl_execute (self.handle, startTime, endTime)
        data = self.convertMatrixToNumpy (m)
        self.freeMatrix (m)
        return data
    
    # Run a Gillespie simulation, starting at timeStart and ending at timeEnd. Output numberOfPoints evenly spaced.
    def executeOnGrid (self, startTime, endTime, numberOfPoints):  
        m = self.gl.gl_executeOnGrid (self.handle, startTime, endTime, numberOfPoints)
        data = self.convertMatrixToNumpy (m)
        self.freeMatrix (m)
        return data
    
    # Run a Gillespie simulation for a single step, returns the new time
    def moveOneStep (self, currentTime):
        return self.gl.gl_moveOneStep (self.handle, currentTime)

    # Resent the current species amounts back to their initial conditions
    def reset (self):      
        self.gl.gl_reset(self.handle)
    
   	 # Set the random number generator seed. By default the seed is set to gl_DEFAULT_RANDOM_SEED
    def setSeed (self, seed):
        self.gl.gl_setSeed (seed)
      
   	 # Set the seed using the current time - time (NULL). Return the seed that was used
    def setSeedUsingTime (self):
        return self.gl.gl_setSeedByTime()
        
    def getNumberOfMatrixRows (self, m):       
        return self.gl.gl_getMatrixRows (m)        
    
    def getNumberOfMatrixCols (self, m):       
        return self.gl.gl_getMatrixCols (m)        
    
    def getMatrixValue (self, m, row, col):       
        return self.gl.gl_getMatrixValue (m, row, col) 
    
    def freeMatrix (self, m):       
        self.gl.gl_freeMatrix (m)
        
    def convertMatrixToNumpy (self, m):
        
        rows = self.getNumberOfMatrixRows (m)
        cols = self.getNumberOfMatrixCols (m)
              
        newMatrix = np.empty([rows, cols])
        for i in range (rows):
            for j in range (cols):
                newMatrix[i,j] = self.gl.gl_getMatrixValue (m, i, j)
        return newMatrix        
        
