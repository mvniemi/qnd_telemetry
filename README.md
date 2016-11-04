# qnd_telemetry
"Quick and Dirty" Telemetry
A basic telemetry system for RC Aircraft using inexpensive NR24 radio module and the Arduino Pro Mini.

The framework is a pair of Arduinos and NR24 radios that transmit data from a remote unit on the aircraft to a 
base station on the ground

I also have made a python module that takes in this data over serial connection to the base station and implements
an audio variometer and altitude call outs.

The point of this project is to minimize abstraction and proprietary hardware so that you can get your raw data and play around with it on
your PC or expand out on your arduino base station. 

Currently on my remote unit I have a bmp_180 barometer and a voltage divider circuit to determine altitude and battery voltage.

![alt text](https://cdn.rawgit.com/mvniemi/qnd_telemetry/master/schematics/Telem_Remote_schem.svg)
