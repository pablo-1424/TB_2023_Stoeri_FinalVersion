import time
import serial
import matplotlib.pyplot as plt

# Serial configuration, normally this is enough information
ser = serial.Serial('COM5', 115200)

# Number of serial value reads
testDuration = 1000

# Arrays for the serial Values
xpoints = []
ypoints = []
yOnPoints = []
yTimPoints = []

for x in range(testDuration):
    serVal = ser.readline().decode().strip()
    print(serVal)
    vals = serVal.split('\x00')
    xy = vals.pop()
    xy12Sep = xy.split(",")
    if len(xy12Sep) == 4:
        xpoints.append(int(xy12Sep[3]) / 800 * 1000)
        yTimPoints.append(int(xy12Sep[2]))
        ypoints.append(int(xy12Sep[1]) / 1024)
        if len(xy12Sep[0]) != 1:
            yOnPoints.append(int(xy12Sep[0]))
        else:
            yOnPoints.append(int(xy12Sep[0]))

    # Copy values in a file
    # To be safe and maybe re-use them if necessary
    file1 = open('testLab.txt', 'a')
    localtime = time.asctime(time.localtime(time.time()))
    file1.write("Test plot_AlternateWithWater_1 : \n" + localtime + "\n\n")
    file1.write("x points \n")
    file1.write(str(xpoints) + "\n\n")
    file1.write("Accel points \n")
    file1.write(str(ypoints) + "\n\n")
    file1.write("On/Off points \n")
    file1.write(str(yOnPoints) + "\n\n\n")
    file1.close()

# Adjusting for not superposing titles and graphs
fig = plt.figure()
fig.subplots_adjust(hspace=0.5, wspace=0.5)

# Plot the acceleration datas
plt.subplot(2, 1, 1)
plt.scatter(xpoints, ypoints, s=5)
plt.title("Accélération ")
plt.xlabel("Temps ms")
plt.ylabel("Accélération résultante en g")

# Plot the On/Off datas
plt.subplot(2, 1, 2)
plt.plot(xpoints, yOnPoints)
plt.title("Eau On/Off")
plt.xlabel("Temps ms")
plt.ylabel("1 = On, 0 = Off")

#These five lines where to test a timer
#plt.subplot(2, 1, 2)
#plt.plot(xpoints, yTimPoints)
#plt.title("Timer")
#plt.xlabel("Temps ms")
#plt.ylabel("Timer Value")

# Save the plot
plt.savefig('plot_AlternateWithWater_1.png')

# Show the wonderful plot
plt.show()
