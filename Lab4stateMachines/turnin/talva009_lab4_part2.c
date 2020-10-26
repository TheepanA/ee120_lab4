/*	Author: talva009
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Inc, Dec, Zero} state;
unsigned char cnt = 0;

void Tick(){

switch(state){
           case Start:
              break;
           case Init:
              cnt = 7;
              break;
           case Inc:
              cnt++;
              break;
           case Dec:
              cnt--;
              break;
           case Zero:
              cnt = 0;
              break;
           default:
              break;
        };

	switch(state){
	case Start:
	   state = Init;
	   break;
	case Init:
	   if(PINA == 0X01){ state = Inc; }
           else if (PINA == 0x02){ state = Dec; }
	   else if(PINA == 0x03){ state = Zero; }
	   break;	
	case Inc:
	   if(PINA == 0X01){ state = Inc; }
           else if (PINA == 0x02){ state = Dec; }
           else if(PINA == 0x03){ state = Zero; }
           break;	   	
	case Dec:
           if(PINA == 0X01){ state = Inc; }
           else if (PINA == 0x02){ state = Dec; }
           else if(PINA == 0x03){ state = Zero; }
           break; 
	case Zero:
           if(PINA == 0X01){ state = Inc; }
           else if (PINA == 0x02){ state = Dec; }
           else if(PINA == 0x03){ state = Zero; }
           break;
       
	default:
	   break;
	};


	
	PORTC = cnt;

}

int main(void) {
     /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        DDRC = 0XFF;
        PORTC = 0x00; // Initialize PORTB output to 0’s

    state = Start;

    while (1) {
	Tick();	
    }
    return 1;
}
