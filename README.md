# 3D-scanner-prototype
3D scanner prototype made with arduino

First upload the .ino file to the arduino then start executing the python code, first it prompts you to enter the file name to which the 3D model will be created.
The arduino code will first initiate a handshake with the python befre sending the data,after that it will start to send the 'distance angle_of_servo angle_of_stepper' through serial to the system which are then received by the python code and cnverted into 3D points and stored in a list from which a .obj file(3D file format) and text file is created.
The generated 3D model can be viewed with the help of 3D softwares such as Blender and Meshlab.
