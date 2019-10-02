## Summary - Project 1 Final Submission - Chloe Gregory - ceg5409

This .zip contains the following:
CMPSC458_Projects - a folder containing the source files for the project including
	Project_1/Project_1.exe - an executable file to run the project
Project1_Gregory_Chloe.mp4 - a video of the completed project and functionality testing
Readme.md - this file

Input instructions are as follows:
"Project 1 code \n\n"
"Press the U,I,O to increase transformations \n"
"Press the J,K,L to decrease transformations \n"
"\tKey alone will alter rotation rate\n "
"\tShift+Key will alter scale\n "
"\tControl+Key will alter translation\n "
"Pressing G will reset transformations\n ";

My project edits the starter code in the following places:

***Project1.hpp:
line35      : an additional parameter was added to the processInput definition
	      this allows the cubePosition in main to be amended in the processInput function


***Project1.cpp:
line28-39   : global variables keep track of changes to the boxes via user input as well as
	      the initial state for resetting the motion
line206-210 : additional loadTexture calls for the walls of the skybox
line276-278 : process rotation according to global rotation variables which may have been
	      edited by the user
line288-290 : update the speed of the rotation to the possibly updated speed variables
line307-367 : draws the additional sides of the skybox. this is done by placing the added
	      walls over the initial wall and then rotating appropriately
line370     : uncommented the Draw call and changed the texture to match the bottom of the
	      skybox
line405-519 : processes user keypresses and updates global tracking variables and cube position


***heightmap.hpp
line72-90   : renders the heightmap mesh with respect to the bottom of the skybox
line116-141 : defines and creates heightmap vertices
line158-167 : sets up the VAO, VBO, and EBO similar to the implementation for the boxes in main