import os
import tkinter
from tkinter import filedialog
#import tkmessagebox
#import tkfiledialog
dialog1 = tkinter.Tk()
dialog1.geometry("300x200")
def loader():
    os.system('python scanner_mark1_loader.py')
def scanner():
    os.system('python scanner_mark1_scan.py')
b1 = tkinter.Button(dialog1 , text="LOADER",bg='black',fg='white',font="white",height=5,bd=5,width=10, command=loader)
b2 = tkinter.Button(dialog1 , text="SCANNER",bg='black',fg='white',font="white",height=5,bd=5,width=10, command=scanner)
b1.pack()
b2.pack()
dialog1.mainloop()
