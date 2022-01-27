import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import pchip_interpolate

"""
import sys

inputColors = []
if len(sys.argv) > 1:
    inputColors = sys.argv[1:]

for colorString in inputColors:
    colorString
"""
#set up the control points for your gradiant
#I included values on either side of the end points to make the gradiant wrap around more smoothly (no sharp corners)
yR_observed = [242, 34, 34, 141, 237, 31, 34, 34]
yG_observed = [155, 153, 131, 74, 99, 133, 153, 131]
yB_observed = [178, 46, 153, 212, 242, 156, 46, 153]

x_observed = [-.1425, 0, .16, .42, .6425, .8575, 1, 1.16]

#Create the arrays with the interpolated values
x = np.linspace(min(x_observed), max(x_observed), num=1000)
yR = pchip_interpolate(x_observed, yR_observed, x)
yG = pchip_interpolate(x_observed, yG_observed, x)
yB = pchip_interpolate(x_observed, yB_observed, x)

#Convert them back to python lists
x = list(x)
yR = list(yR)
yG = list(yG)
yB = list(yB)

#Find the indexs where x crosses 0 and crosses 1 for slicing
start = 0
end = 0
for i in x:
    if i > 0:
        start = x.index(i)
        break

for i in x:
    if i > 1:
        end = x.index(i)
        break

#Slice away the helper data in the begining and end leaving just 0 to 1
x = x[start:end]
yR = yR[start:end]
yG = yG[start:end]
yB = yB[start:end]

#Plot the values if you want

#plt.plot(x, yR, color = "red")
#plt.plot(x, yG, color = "green")
#plt.plot(x, yB, color = "blue")
#plt.show()

#Send values to file with your favorite method
#I used python fileName.py > outputFile.txt method
for i in range(len(yB)):
    print(str(int(yR[i]))+","+str(int(yG[i]))+","+str(int(yB[i])))
