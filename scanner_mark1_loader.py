import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import tkinter
from tkinter  import filedialog
#from mayavi import mlab
dialog = tkinter.Tk()
dialog.geometry("300x400")
filename = filedialog.askopenfile()
#mlab.figure(1, fgcolor=(0, 0, 0), bgcolor=(1, 1, 1))
fig = plt.figure()
ax = fig.gca(projection='3d')
with open(filename.name , 'r') as file:
    linelists = file.readlines()
points=[[],[],[]]
print(linelists)
line1 = linelists[0]
line2 = linelists[1]
line3 = linelists[2]
points[0] = list(map(float,line1[1:len(line1)-2].split(",")))
points[1] = list(map(float,line2[1:len(line2)-2].split(",")))
points[2] = list(map(float,line3[1:len(line3)-2].split(",")))
def binary():
    ax.plot_trisurf(points[0],points[2],points[1],cmap = 'binary')
    plt.show()
    
'''def mayavi():
    pts = mlab.points3d(points[0],points[1],points[2],points[2], scale_mode='none', scale_factor=0.2)
    mesh = mlab.pipeline.delaunay2d(pts)
    surf = mlab.pipeline.surface(mesh)

    mlab.view(47, 57, 8.2, (0.1, 0.15, 0.14))
    mlab.show()
'''
    
    
def plotting():
    ax.plot(points[0],points[2],points[1],'ro')
    plt.show()
def exitnow():
    exit()
def allstyles():
    fig ,ax=plt.subplots(nrows=2,ncols=2,subplot_kw={'projection':'3d'})
    ax[0,0].plot_trisurf(points[0],points[2],points[1],cmap = 'binary')
    ax[0,1].plot_trisurf(points[0],points[2],points[1],cmap = 'viridis')
    ax[1,0].plot(points[0],points[2],points[1],'ro')
    plt.show()
def box():
    dialog = tkinter.Tk()
    dialog.geometry("300x600")
    but1 = tkinter.Button(dialog , text="PLOT",bg='black',fg='white',font="white",height=5,bd=5,width=10, command=plotting)
    but2 = tkinter.Button(dialog , text="TRI_SURF",bg='black',fg='white',font="white",height=5,bd=5,width=10, command=binary)
    but4 = tkinter.Button(dialog , text="EXIT" , bg='black',fg='white',font='white',bd=5,height=5,width = 10,command =exitnow)
    but5 = tkinter.Button(dialog , text="ALL STYLES" , bg='black',fg='white',font='white',bd=5,height=5,width = 15,command =allstyles)
    but1.pack()
    but2.pack()
    #but3 = tkinter.Button(dialog , text="MAYAVI",bg='black',fg='white',font="white",height=5,bd=5,width=10, command=mayavi)
    #but3.pack()
    but5.pack()
    but4.pack()
    dialog.mainloop()
    #plt.show()
    input("done")

while True:
    box()
    #ax.plot_trisurf(points[0],points[1],points[2],cmap = 'binary')
    #ax.plot_trisurf(points[0],points[1],points[2],cmap = 'viridis')
    #ax.plot(points[0],points[1],points[2],'ro')
