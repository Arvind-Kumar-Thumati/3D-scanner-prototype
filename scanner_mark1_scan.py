from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from time import sleep
import serial
import tkinter as tk
from tkinter import filedialog
import math

dialogbox = tk.Tk()
#dialogbox.geometry("200x200")
def fileselected():
    global filename
    filename = entry.get()
        
tk.Label(dialogbox,text='enter file name').grid(row=0)
entry = tk.Entry(dialogbox)
entry.grid(row=0, column=1)
tk.Button(dialogbox,text='OK',command=fileselected).grid(row=2,column=0,sticky=tk.W,pady=4)

dialogbox.mainloop()
points=[[],[],[]]
i=0
flag = 0
ser = serial.Serial('com2',baudrate=9600,timeout=1) 
fig, ax1 = plt.subplots(nrows=2, ncols=2, subplot_kw={'projection': '3d'})
#file =open(filename+".txt","w+")

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
                val=list(temp.split())
                values= [ float(x) for x in val]
                print(values)
                dist = math.cos(values[1]*math.pi/180)*values[0]
                points[0].append(float(dist * math.cos(values[2]*math.pi/180)))
                points[1].append(float(dist * math.sin(values[2]*math.pi/180)))
                points[2].append(float(values[0] * math.sin(values[1]*math.pi/180)))
        
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

#print(points)
ax1[0,0].plot(points[0],points[1],points[2],'ro')
#ax1[0,1].plot_wireframe(points[0],points[1],points[2],rstride=40,cstride=40)
#ax1[0,2].plot_wireframe(points[0],points[1],points[2],rstride=5,cstride=5)
#ax1[1,0].plot_trisurf(points[0],points[1],points[2],cmap='binary')
#ax1[1,1].plot_trisurf(points[0],points[1],points[2],cmap='viridis')
#ax1[2,1].plot_trisurf(points[0],points[1],points[2],cmap='viridis')
#ax1.set_xlabel("X Axis")
#ax1.set_ylabel("Y Axis")
#ax1.set_zlabel("Z Axis")
plt.show()
plt.savefig(filename+".png")
print("done")
sleep(1)
