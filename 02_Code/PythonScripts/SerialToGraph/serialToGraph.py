import serial
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('COM5',115200)



xpoints = []
ypoints = []

for x in range(1000) :
    serVal = ser.readline().decode().strip()
    print(serVal)
    vals = serVal.split('\x00')
    xy = vals.pop()
    xySep = xy.split(",")
    if len(xySep) == 2:
        xpoints.append(int(xySep[1])/800*1000)
        ypoints.append(int(xySep[0]))

plt.scatter(xpoints, ypoints)
#plt.axline(xy1=( color="red")
plt.title("Accélération ")
plt.xlabel("Temps ms")
plt.ylabel("Accélération résultante en g")
plt.show()