/*
 *
 * Author: 
 * 11/29/2022
 * 
 */


/*
 Lab 6 Starter Code
 * Simon Says Final Project
 
 */

// PIC16F1829 Configuration Bit Settings
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)




/*Serial Configuration*/
#define BAUD 9600   //Bits per second transfer rate
#define FOSC 4000000L   //Frequency Oscillator
#define DIVIDER ((int)(FOSC/(16UL * BAUD) -1))  //Should be 25 for 9600/4MhZ
#define NINE_BITS 0
#define SPEED 0x4       //T Speed
#define RX_PIN TRISC5   //Recieve Pin
#define TX_PIN TRISC4   //Transmit Pin

/*Xtal Macro*/
#define _XTAL_FREQ 4000000.0    /*for 4mhz*/

//Function Prototypes
void setup_comms(void);
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);
void timer_config(void);
void clockAndpin_config(void);
void usartConfig(void);
void Display (int);

int main(int argc, char** argv) {
/*Variable Declaration*/  
    unsigned int Tcount, Threshold;
    int Touch[4], mode;
/*TouchPad Setup*/  
    CPSCON0 	=   0x8C;   //Set up Touch sensing module control reg 0
    Touch[0] = 3; // RA4 pad CPS3
    Touch[1] = 9; // RC7 pad CPS9
    Touch[2] = 5; // RC1 pad CPS5
    Touch[3] = 4; // RC0 pad CPS4

/*Clock and Pin Configuration*/
    clockAndpin_config();      //Configures clock and pins, enables timers
    
/*USART CONFIG*/
    usartConfig();
    setup_comms();
    
/*Threshold Value*/
    Threshold 	=   0x0000; //using the threshold for all 3 channels
    
/*Start Replace*/  
/*Infinite While*/
    while (1){
        mode = 4;  // Now initialize the timer0 and 1 and scan 3 pads
        for (int j = 0; j < 4; j++) {
            CPSCON1 = Touch[j];
            timer_config();
            while (!TMR0IF) continue; //wait here till Timer 0 overflows
            Tcount = (TMR1H << 8) + TMR1L; //Save 16 bit count value in timer 1
            printf("Tcount = %x, Threshold= %x \r\n", Tcount, Threshold); //Write to UART TERMINAL
            __delay_ms(200);
            TMR0IF = 0; //Clear the interrupt flag for Timer 1
            if (Tcount < Threshold) mode = j;
        }
        Display(mode);
    }
/*End Replace*/
 return (EXIT_SUCCESS);
}


// void Display(int delay) {
//            switch (delay) {
//                case 0: //Case for button U
//                    RA5 = ~RA5;
//                    __delay_ms(100);
//                    break;
//                case 1: //Case for button T
//                    RA5 = 1;
//                    __delay_ms(250);
//                    RA5 = 0;
//                    __delay_ms(250);
//                    break;
//                case 2: //Case for button S
//                    RA5 = 1;
//                    __delay_ms(175);
//                    RA5 = 0;
//                    __delay_ms(175);
//                    break;
//                case 3: //Case for button A
//                    RA5 = 1;
//                    __delay_ms(175);
//                    RA5 = 0;
//                    __delay_ms(175);
//                    RA5 = 1;
//                    __delay_ms(300);
//                    RA5 = 0;
//                    __delay_ms(300);
//                    break;
//                case 4: // Default, No Touch
//                    break;
//    }

//}

void startGame(){
printf("Welcome to simon says! Press the push button to start /n");
if (RB7 = 1){
  printf("Watch the order of the colors and repeat the sequence /n");
  __delay__ms(500);
}
else
  return();
}

void level_1(){
  printf("Level 1 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}

void level_2(){
  printf("Level 2 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}

void level_3(){
  printf("Level 3 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}

void level_4(){
  printf("Level 4 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}

void level_5(){
  printf("Level 5 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}

void level_6(){
  printf("Level 6 /n");
  __delay__ms(1000);
  printf("Ready, set, go! /n");
  __delay__ms(1000);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  RC6 = 1;                    // Blink on/off red
  __delay__ms(800);
  RC6 = 0;
  __delay__ms(800);
  RA5 = 1;                    // Blink on/off green
  __delay__ms(800);
  RA5 = 0;
  __delay__ms(800);
  RA2 = 1;                    // Blink on/off blue
  __delay__ms(800);
  RA2 = 0;
  __delay__ms(800);
  printf("Please repeat the sequence /n");
  if (RA4 = 1){
    

  }
}


void clockAndpin_config(){
    OSCCON      =	0X6A;  	//set up 4MHz for Fosc
    INTCON      =   0;      // purpose of disabling the interrupts.
    OPTION_REG  =   0XC5;  	// set up timer 0, and then timer 1
    T1CON    	=	0XC1;   //TMR 1 Enable
    T1GCON   	=  	0X81;   //81 is without toggle mode A1 is toggle mode
    TRISA   	= 	0X10;
    TRISC   	=	0XFF;
    PORTA   	= 	0;
    ANSELA  	=   0X10;
}

void timer_config(){
    TMR1ON  	=   0;
    TMR0    	=   0;
    TMR1H       =   0;
    TMR1L   	=   0;
    TMR1ON      =   1;
    TMR0IF  	=   0;      	//Clear the interrupt flag for Timer 1
    TMR0    	=   0;  
}

void usartConfig(){
    APFCON0 = 0x84; //This sets pins RC5 and RC4 as RX & TX on pic16f1829
    TXCKSEL = 1;   
    RXDTSEL = 1;  //makes RC4 & 5 TX & RX for USART (Allows ICSP)
}

void setup_comms(void){

	RX_PIN = 1;
	TX_PIN = 1;
	SPBRG = DIVIDER;
	RCSTA = (NINE_BITS|0x90);
	TXSTA = (SPEED|NINE_BITS|0x20);
    	TXEN=1;
    	SYNC=0;
    	SPEN=1;
    	BRGH=1;
}

void putch(unsigned char byte)
{
	/* output one byte */
	while(!TXIF)	/* set when register is empty */
		continue;
	TXREG = byte;
}

unsigned char getch() {
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
        continue;
	return RCREG;
}

unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}
