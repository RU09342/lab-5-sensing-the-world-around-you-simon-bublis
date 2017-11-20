# PCB Design

This PCB design is used as a breakout board for the MSP430FR2311, which can conveniently fit on a breadboard and contains the required passives for this processor to work in a standalone implementation.

## Schematic

![alt text](https://github.com/RU09342/lab-5-sensing-the-world-around-you-simon-bublis/blob/master/PCB%20Design/Screenshots/Schematic.PNG)

In the schematic all the pins of the MSP430FR2311 microcontroller are connected to headers that will be used to plug into a breadboard.C1 is a bulk 
capacitor used to prevent the output of the supply from dropping too far during the period when current is not available.C2 is a bypass capacitor used 
to remove any noise that is present on a DC signal. C3 is used to enable highspeed SBW communication. The capacitors are grounded to DVSS on the microcontroller.

## PCB Specifications

When designing the PCB the most important part is the distance between the headers so it is able to plug into a breadboard. The distance between the 
headers can either be 0.5 inches or 0.7 inches, this depends on the size board you want to use.In this design a 0.5 inch spacing was used for a compact 
design.Use a 0.7 inch spacing if you are having trouble running all the traces. Make sure to use traces that are 6 mils or wider.  

## Final Design
![alt text](https://github.com/RU09342/lab-5-sensing-the-world-around-you-simon-bublis/blob/master/PCB%20Design/Screenshots/PCB%20Top%20View.PNG) ![alt text](https://github.com/RU09342/lab-5-sensing-the-world-around-you-simon-bublis/blob/master/PCB%20Design/Screenshots/PCB%20Bottom%20View.PNG)

![alt text](https://github.com/RU09342/lab-5-sensing-the-world-around-you-simon-bublis/blob/master/PCB%20Design/Screenshots/3d%20View.PNG) ![alt text](https://github.com/RU09342/lab-5-sensing-the-world-around-you-simon-bublis/blob/master/PCB%20Design/Screenshots/3d%20Back%20View.PNG)

### Bill of Materials

|RefDes     | Name     	   	 |Value|
|-----------| ------------------ |-----|
|C1         | CAP_0805 	   	 |100nF|
|C2         | CAP_0805 	   	 |10nF |
|C3         | CAP_0805	   	 |1nF  |
|J1         | 64456_8 	   	 |N/A  |
|J2         | 64456_8 	   	 |N/A  |
|R1         | RES_0805 	   	 |47k  |
|U1         | MSP430FR2311IPW16R |N/A  |

DigiKey Link: http://www.digikey.com/short/q37hf4