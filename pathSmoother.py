import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import pchip_interpolate

def smoothPath():
    #set up the control points for the smooth path
    targetReal = []
    targetImaginary = []
    targetWidth = []

    #Read in all the targets that the user just chose
    f = open("targets.txt", "r")
    next(f)
    for line in f:
        myValues = line.split(", ")
        targetReal.append(myValues[0])
        targetImaginary.append(myValues[1])
        targetWidth.append(myValues[2].replace("," ,"").replace("\n", ""))
    f.close()


    #Create the arrays with the interpolated values
    #Specify -1 for x to stop the interpolator from creating values past the last target
    x_observed = range(len(targetReal))
    x = np.linspace(0, (len(targetReal)-1), num=((len(targetReal)-1)*30))
    yReal = pchip_interpolate(x_observed, targetReal, x)
    yImaginary = pchip_interpolate(x_observed, targetImaginary, x)
    yWidth = pchip_interpolate(x_observed, targetWidth, x)

    #Convert them back to python lists
    x = list(x)
    yReal = list(yReal)
    yImaginary = list(yImaginary)
    yWidth = list(yWidth)

    #Write all the smoothed cordinates to the file
    f = open("frameCordinates.txt", "a")
    for i in range(len(yReal)):
        f.write(str(yReal[i])+", "+str(yImaginary[i])+", "+str(yWidth[i])+"\n")
    f.close()
