/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    P6SEL |= 0x01;                          // ADC => P6.1
    REFCTL0 &= ~REFMSTR;                    // Reset REFMSTR for control reference voltages

    //Initialize ADC12CTL0
    ADC12CTL0 = ADC12SHT0_4+ADC12REFON+ADC12REF2_5V+ADC12ON;
    // 64 ADC12CLK cycles, ADC12_A ref gen on, ADC12_A set to 2.5V, ADC12_A on

    //Initialize ADC12CTL1
    ADC12CTL1=ADC12SHP;                     // SAMPCON signal is sourced from the sampling timer.

    //Set conversion memory control register
    ADC12MCTL0 = ADC12SREF_1+ADC12INCH0;    // VR+ = VREF+ and VR- = AVSS

    ADC12IE = 0x01;                         // Enable interrupt
    ADC12CTL0 |= ADC12ENC;                  // Enable conversion

        P3SEL |= BIT3;                      // P3.3 => TX
        P3SEL |= BIT4;                      // P3.4 => RX
        UCA0CTL1 |= UCSWRST;                // Resets state machine
        UCA0CTL1 |= UCSSEL_2;               // SMCLK
        UCA0BR0 = 6;                        // 9600 Baud Rate
        UCA0BR1 = 0;                        // 9600 Baud Rate
        UCA0MCTL |= UCBRS_0;                // Modulation
        UCA0MCTL |= UCBRF_13;               // Modulation
        UCA0MCTL |= UCOS16;                 // Modulation
        UCA0CTL1 &= ~UCSWRST;               // Initializes the state machine
        UCA0IE |= UCRXIE;

    //Start sampling
    while (1)
    {
        __delay_cycles(1000);
        ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
        __bis_SR_register(LPM0_bits + GIE);     // LPM0, ADC12_ISR will force exit
        __no_operation();                       // For debugger
    }
}

// Confirm TX buffer is ready and display RX value
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{

        while (!(UCA0IFG&UCTXIFG));     // USCI_A0 TX buffer ready?
        if(UCA0RXBUF == 32)             // Press 'Space' to get data
            UCA0TXBUF = ADC12MEM0 >> 4; // Get the ADC12 value and transfer it
                                        // Shift 4 bit to ignore the error
        else
        UCA0TXBUF = 1;                  // Wrong button
}
// Interrupt service
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
}
