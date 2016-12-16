# EvoSim
A basic evolution simulation program written in C++ using GLUT graphics.

## Installation
Be sure to download all files into the same directory to use. Open a terminal window and change directories to the directory with the EvoSim files. Here is an example of the commands with a directory named "EvoSim":

yourdevice:~ you$ cd ~/EvoSim

To compile the program, enter the following commands in the command line of the terminal window:

yourdevice:EvoSim you$ make

The Makefile will run the necessary commands for compiling. This only needs to be done once, after the proper commands are run once, EvoSim can be used without the "make" command. You are ready to use **EvoSim**!

## Running EvoSim
Enter the following command into your terminal window to run the simulation:

yourdevice:EvoSim you$ ./evosim

A window will appear with a random initial population. Watch the simulation to see how this random sample evolves in the environment. The window can change sizes as much as desired.

To exit the simulation, simply press ESC.

## Parameters
The shapes indicate the type of organism. Fill Colors indicate the dominant trait of each species. Outlne colors indicate a secondary trait.

The Shape Codes are as follows:
Triangles: Predators (Carnivores)
Circles: Prey (Herbivores)
Squares: Plants (all green)

The Color Codes are as follows:
Red: Speed
Yellow: Stamina rate
Pink/Purple: Sense (awareness)
Blue: Mate rate
Orange: Life Span
Cyan: Hunger rate
