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
  WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

      // ADC10 Initialization
      ADC10CTL1 = INCH_7 + SHS_1;       // P1.7, TA1 trigger sample start
      ADC10AE0 = BIT7;                  // ADC10 = P1.7

      // Timer Initialization
      TA0CCTL0 = CCIE;                  // Enable interrupt
      TA0CCR0 = 5;                      // PWM Period
      TACCTL1 = OUTMOD_3;               // TACCR1 set/reset
      TACCR1 = 3;                       // TACCR1 PWM Duty Cycle
      TA0CTL = TASSEL_1 + MC_1 + ID_3;  // ACLK/CONTINUOUS MODE

      // UART Initialization
  if (CALBC1_1MHZ==0xFF)                // Run if calibration constant is erased
        {
          while(1);
        }

        P1SEL = BIT1 + BIT2;            // P1.1 => RXD / P1.2=> TXD
        P1SEL2 = BIT1 + BIT2;           // P1.1 => RXD / P1.2=> TXD

        UCA0CTL1 |= UCSSEL_2;           // SMCLK
        UCA0BR0 = 104;                  // 9600 baud rate
        UCA0BR1 = 0;                    // 9600 baud rate
        UCA0MCTL = UCBRS0;              // Modulation UCBRSx = 1
        UCA0CTL1 &= ~UCSWRST;           // Initialize USCI state machine
        IE2 |= UCA0RXIE;                // Enable USCI_A0 RX interrupt

        // Clock Initialization
        DCOCTL = 0;                     // Select lowest DCOx and MODx settings
        BCSCTL1 = CALBC1_1MHZ;          // Set DCO
        DCOCTL = CALDCO_1MHZ;

  __enable_interrupt();
  __bis_SR_register(GIE);               // interrupt enable
    while(1){
    }
}

// Confirm TX buffer is ready and display RX value
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2&UCA0TXIFG));          // Wait till USCI_A0 TX buffer ready

    if(UCA0RXBUF == 32)                 // Press 'Space' to get data
        UCA0TXBUF = ADC10MEM >> 4;      // Get the ADC10 value and transfer it
                                        // Shift 4 bit to ignore the error
    else
    UCA0TXBUF = 1;                      // Wrong button pressed
}
//Timer ISR
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)

{
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON; // ADC10 On
    ADC10CTL0 |= ENC;                                  // ADC10 enable set
}
