# VisualGPSqt
A QT application (GUI) that makes use of the https://github.com/VisualGPS/NMEAParser project. You should be able to build this project using your favorite operating system (Linux, Windows, or Mac OS).
![Qt Project making use of the NMEAParser.](./img/ss.png)

## Building VisualGPSqt

VisualGPSqt uses the NMEAParser and is included in this project as a git submodule. Make sure that you initialize and update git submodules. See below for more information. As for building VisualGPSqt, Simply use qtcreator IDE to open the .pro file and compile as normal. 

## Linux build
 * Make sure that you initialize and update the submodule.
 ```bash
   git submodule init
   git submodule update
 ```
 * Using qtcreator, open VisualGPSqt/Software/VisualGPSqt/Source/VisualGPSqt.pro
 - Compile as normal
 - **NOTE:** You may have to run as administrator depending on your permissions to access the serial port.

 ## Windows Build
  * Make sure that you initialize and update the submodules.
 ```bat
   git submodule init
   git submodule update
 ```
 * Using qtcreator, open VisualGPSqt/Software/VisualGPSqt/Source/VisualGPSqt.pro
 - Compile as normal
