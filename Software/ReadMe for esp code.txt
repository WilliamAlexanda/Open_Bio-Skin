Author: Haoran Guo(haoran.guo@okstate.edu), Oklahoma State University, MIR Lab

Hi, welcome to use Bio-Skin v1.0. 

Bio-Skin is aim to achieve a multi-modal cost effective tactile sensor, which can sense normal, shear force, 
temperature and achieve self temperature regulation.

*Sensor Setup
1. Connect wire between esp32 and MUX board. Pin definition of esp32: 
1 - S0
2 - S1
3 - S2
4 - S3
5 - Out
6 - (Default to plug off) Heat
GND - GND
3.3V - Vcc
3.3V - Vcc2 (For heating function)

2. Connect the Bio-Skin and Mux board by FPC ribbon.

3. Use the <COM> port on esp32 to connect the USB cable.

4. Open the arduino IDE and its serial monitor (or other serial monitor).

5. Connect the USB cable to the PC, and check the new COM port number for Bio-skin and the output of the serial port. 
(Baud rate: 250000)
The correct output include 11 sets of raw ADC data and seperate by comma.
Example: [Normal Force(NF)1, NF2, NF3, NF4, NF5, Shear Force(SF)1, SF2, SF3, SF4, Temperature, Data for calibration]
Then close the serial monitor to release the port.







