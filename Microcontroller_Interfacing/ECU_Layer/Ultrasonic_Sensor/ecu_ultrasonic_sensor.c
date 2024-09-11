/* 
 * File:   ecu_ultrasonic_sensor.h
 * Author: Ziad_Elmekawy
 *
 * Created on 22 August, 2024, 06:39 PM
 */

/*
 * Description:
 * 
 *                         PIC18F4620
 *                 +----------:_:----------+
 *       VPP ->  1 : RE3/MCLR/VPP  PGD/RB7 : 40 <> PGD
 *           <>  2 : RA0/AN0       PGC/RB6 : 39 <> PGC
 *           <>  3 : RA1           PGM/RB5 : 38 <>
 *           <>  4 : RA2               RB4 : 37 <>
 *           <>  5 : RA3               RB3 : 36 <> LED_D5
 *           <>  6 : RA4          INT2/RB2 : 35 <> LED_D4
 *           <>  7 : RA5          INT1/RB1 : 34 <> LED_D3
 *           <>  8 : RE0          INT0/RB0 : 33 <> LED_D2
 *           <>  9 : RE1               VDD : 32 <- PWR
 *           <> 10 : RE2               VSS : 31 <- GND
 *       PWR -> 11 : VDD               RD7 : 30 <> 
 *       GND -> 12 : VSS               RD6 : 29 -> LCD_E
 *           <> 13 : RA7/OSC1          RD5 : 28 -> LCD_RW
 *           <> 14 : RA6/OSC2          RD4 : 27 -> LCD_RS
 *           <> 15 : RC0/SOSCO   RX/DT/RC7 : 26 <> 
 *           <> 16 : RC1/SOSCI   TX/CK/RC6 : 25 <> 
 *      ECHO -> 17 : RC2/CCP1          RC5 : 24 -> TRIGGER
 *           <> 18 : RC3/SCL       SDA/RC4 : 23 <> 
 *    LCD_D4 <> 19 : RD0               RD3 : 22 <> LCD_D7
 *    LCD_D5 <> 20 : RD1               RD2 : 21 <> LCD_D6
 *                 +-----------------------:
 *                          DIP-40
 *
 * See:
 */

#include <stdio.h>
#include "ecu_ultrasonic_sensor.h"

void init_timer(void) {
    T1CON = 0x10;  // Configure Timer1 with 1:2 prescale
}

/* ENABLE THIS FUNCTION WHEN USING THIS MODULE 
void init_ultrasonic(void) {
    TRISDbits.TRISB0 = 0;  // TRIG_PIN as output
    TRISDbits.TRISB1 = 1;  // ECHO_PIN as input
    TRIG_PIN = 0;          // Set TRIG_PIN low
}
*/
uint16 measure_distance(void) {
    unsigned int time = 0;
    unsigned int distance = 0;

    // Send a 10us pulse to the TRIG_PIN
    TRIG_PIN = 1;
    __delay_ms(10);
    TRIG_PIN = 0;

    // Wait for the ECHO_PIN to go high
    while(!ECHO_PIN);

    // Start Timer1 when ECHO_PIN goes high
    TMR1H = 0;
    TMR1L = 0;
    T1CONbits.TMR1ON = 1;                                                        /* REMOVE THIS COMMENT WHEN USING THIS MODULE */

    // Wait for the ECHO_PIN to go low
    while(ECHO_PIN);

    // Stop Timer1 and calculate the time
    T1CONbits.TMR1ON = 0;                                                        /* REMOVE THIS COMMENT WHEN USING THIS MODULE */
    time = (TMR1H << 8) + TMR1L;

    // Calculate distance in cm (speed of sound is approximately 343 m/s)
    distance = (time * 0.034) / 2;

    return distance;
}