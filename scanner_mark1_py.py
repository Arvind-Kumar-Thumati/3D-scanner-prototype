from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from time import sleep
import serial
import pickle

points=[[],[],[]]
i=0
flag = 0
filename = "avt_box_2"

ser =serial.Serial('com2',baudrate=9600,timeout=1) 
fig, ax1 = plt.subplots(nrows=2, ncols=2, subplot_kw={'projection': '3d'})
file = open(filename+".txt","w+")
while (flag==0):
    temp=[]
    temp=ser.readline().decode('utf-8').rstrip()
    print(temp)
    if "ready" in temp:
        send='1'
        ser.write(bytes(send,'utf-8'))
        while True:
            temp=[]
            temp=ser.readline().decode('utf-8').rstrip()
            print(temp)
            if(temp=="end"):
                flag=1
                break
            
            if(temp=="next"):
                print(temp)
                sleep(2)
                continue
            if(len(temp)!=0):
                values=list(temp.split())
                print(values)
                points[0].append(float(values[0]))
                points[1].append(float(values[1]))
                points[2].append(float(values[2]))
        
            i+=1
with open(filename+".txt", 'w') as filehandle:  
    filehandle.writelines("%s\n" % coordinates for coordinates in points)

xp = points[0]
yp = points[1]
zp = points[2]
vertices=[]
for i in range(len(xp)):
    temp =[]
    temp.append(xp[i])
    temp.append(yp[i])
    temp.append(zp[i])                
    vertices.append(temp)
#print(vertices)

with open( filename+".obj" , 'w') as file :
    file.write("# OBJ file of "+filename+"\n")
    for i in range(len(vertices)):
        file.write("v ")
        file.write(str(vertices[i][0]))
        file.write(" ")
        file.write(str(vertices[i][1]))
        file.write(" ")
        file.write(str(vertices[i][2]))
        file.write("\n")

plt.savefig(filename+".png")
plt.show()

#print(points)
ax1[0,0].plot(points[0],points[1],points[2],'r-')
ax1[0,1].plot(points[0],points[1],points[2],'ro')
#ax1[1,0].plot(points[0],points[1],points[2],'ro')#,rstride=5,cstride=5)
#ax1[1,0].plot_trisurf(points[0],points[1],points[2],cmap='binary')
#ax1[1,1].plot_trisurf(points[0],points[1],points[2],cmap='viridis')
#ax1[2,1].plot_trisurf(points[0],points[1],points[2],cmap='viridis')
#ax1.set_xlabel("X Axis")
#ax1.set_ylabel("Y Axis")
#ax1.set_zlabel("Z Axis")
print("done")
sleep(1)
