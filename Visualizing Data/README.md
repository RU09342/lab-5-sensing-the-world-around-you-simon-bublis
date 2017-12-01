# Visualizing Data

The goal of this section of lab was to take the digital signals the were convereted by the ADC and visually display them. 

The only board that can be used fot this section is the MSP430-FR6989 since it has the on-board LCD screen. The 6989 takes the analog value from the sensors, converts to digital using 12-bit ADC, and displays the digital reading.

The showChar() function takes in a character that you want to display and an integer that acts as the location to display the character.

```c
    showChar('0',0);
    showChar('0',1);
    showChar('0',2);
    showChar('0',3);
    showChar('0',4);
    showChar('0',5);
    showChar('0',6);
```
The above code shows '0' being displayed on all 6 locations on the LCD display. 

The code below shows how to initialize the analog to digital converter. This is how the MSP can accept and understand the signals coming from the sensors. The code below shows a reference voltage of 2.5V.

```c
//Initialize ADC
void ADCInit()
{
      REFCTL0=REFON + REFVSEL_2;           // Use a Ref Voltage of 2.5V
      ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling time, S&H=16, ADC12 on
      ADC12CTL1 = ADC12SHP;                // Use sampling timer, ADC12SC conversion start,clock=OSC
      ADC12CTL2 |= ADC12RES_2;             // 12-bit conversion results
      ADC12MCTL0 |= ADC12INCH_3;           // ADC input select
      ADC12IER0 |= ADC12IE0;               // Enable ADC conversion complete interrupt
      ADC12CTL0 |= ADC12ENC;               // Enable conversion
      P1SEL0 |=BIT3;                       // Configure P1.3 for input channel 3
      P1SEL1 |=BIT3;
}
```

After the ADC is initialized, the number that is recieved (intger) is converted to a character so that it can be displayed on the LCD.

The circuit for this lab is the same as the one found in the "Signal and Conditioning" section for the photoresistor. The rest of the code for this section is also identical to the previous section with the addition of the new functions found in "LCDDriver.h".


# Instructions
# Visualizing Data
In the next lab, we will start looking into how to take action on the information your microprocessor is receiving, for the last part of this lab, we will focus on visualizing the data. We will focus on three main methods of visualization. For each of these methods, you need to pick between 1-3 processors based on the part. As with Milestone 1, you will need to talk in this README about why you picked the processors you did (for one part, it is going to be painfully obvious). Overall, you should aim to use all five processors by the end of this part of the lab, however _YOU DO NOT NEED TO USE ALL FIVE FOR EACH PART_.

## RGB LED
Hopefully by this point you are fairly comfortable with how to control an RGB LED. To ease into this lab, you should take your sensors and have them correlate to the color, brightness, blinking speed, etc. of an RGB LED. If for your resistive sensor you picked a thermistor, it might make sense to have the RGB change from a "Blue" color to a "Red" color as it heats up. For this, you should pick 3 processors to perform this on. You do not need to use all three sensors on each of the boards. Pick one sensor per board and work off of that.

## LCD Display
Now that you are getting sensor data and acting on it, why don't you actually try to display the information the user in actual numbers. Using the MSP430FR6989, convert the information from all three of your sensors to a human readable value on the on-board LCD. Fair warning, *DO NOT TRY TO REINVENT THE WHEEL*. Make sure you give the resource explorer a good looking through to see what TI is going to provide you. You can utilize the provided LCDDriver.c and LCDDriver.h files in your code.

## PC Visualization
While UART is awesome for talking between processors, it also can be used to stream data back to your computer which you can use software to read. If you want to be adventurous (or if you have experiences in other languages like Python or Java) you can try to make your own visualization software for looking at the sensor data. Instead of that, you need to be able to collect and visualize data through MATLAB using the "Serial Toolbox". It is up to you to figure out how fancy you want your plots to be, but at a minimum, your processor needs to be able to communicate back to MATLAB and you need to be able to plot the data over time back on your laptop. Since this is all UART, I would expect you to do this for at least two processors.

## Now its your turn
For the finale of this lab, pick a processor and run at least two of these visualizations at the same time. You also should look at using multiple channels on the internal ADC, although this is not required.


## Deliverables
For this part of the lab, you need to be able to organize your submissions based on the part of the lab it is fulfilling. If this means using a ton of folders, be my guest, but at the end of the day, I am going to be grading these as if I am someone coming to your repository for information. This whole part can be summarized in one large README which should be *HEAVILY* focused on how to actually implement and use your code. 