# VisualGPSqt
A QT application (GUI) that makes use of the VisualGPS/NMEAParser project.
![Qt Project making use of the NMEAParser.](./img/ss.png)

## Linux build
 * Make sure that you initialize and update the submodule.
 ```bash
   git submodule init
   git submodule update
 ```
 * Using qtcreator, open VisualGPSqt/Software/VisualGPSqt/Source/VisualGPSqt.pro
 - Compile as normal
 - You may have to run as administrator depending on your permissions to access the serial port.

 ## Windows Build
  * Make sure that you initialize and update the submodules.
 ```bat
   git submodule init
   git submodule update
 ```
 * Using qtcreator, open VisualGPSqt/Software/VisualGPSqt/Source/VisualGPSqt.pro
 - Compile as normal
