# Pendulum-Simulation-SFML

A simple simulation of a pendulum using the SFML library

## Features
### Pendulum
- simulates a pendulum
- shows acceleration vectors (gravity->red / centripetal->green / pendulum->blue)
- draws velocity graph for each pendulum
### GUI
+ Features
  * styling system
  * animation: interpolation between styles (default/hovered/clicked)
+ Elements
  * Button  
  * Slider
  * Text


## Build

#### Downloads

| Software             	| **SFML**                                              	| **CMake**                            	| **MinGW**                                             	|
|:------------:	|-------------------------------------------------------	|--------------------------------------	|-------------------------------------------------------	|
| **Version**  	| 2.5.2 MinGW 64                                        	| 3.22+  Msi                               	| 10.3.0 tdm64-gcc                                      	|
| **Download** 	| [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) 	| [CMake](https://cmake.org/download/) 	| [MinGW](https://jmeubank.github.io/tdm-gcc/download/) 

#### Build

- Extract the zip file
- Shift the extractat "SFML-2.5.1" folder into the main folder 
- start cmd inside the main folder and run:
```sh
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```
- start the .exe inside the build folder

## Usage
- Set angle and lenght of pendulum with the Sliders.
- Spawn and reset with buttons
