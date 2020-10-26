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

enum States {OffRelease, OnPress, OnRelease, OffPress} state;

void Tick(){

	switch(state){

	case OffRelease:
	   if(PINA == 0X01){ state = OnPress; }
	   else if (PINA == 0x00){ state = OffRelease; }
	   break;	
	case OnPress:
	   if(PINA == 0x01){ state = OnPress; }
           else if (PINA == 0X00){ state = OnRelease; }
	   break;
	case OnRelease:
          if(PINA == 0X01){ state = OffPress; }
          else if (PINA == 0X00){ state = OnRelease; }
          break;
        case OffPress:
          if(PINA == 0X01){ state = OffPress; }
          else if (PINA == 0X00){ state = OffRelease; }
          break;

	default:
	   break;
	};


	switch(state){
	   case OffRelease:
	      PORTB = 0x01;
	   case OnPress:
	      PORTB = 0X02;
	   case OnRelease:
              PORTB = 0x02;
           case OffPress:
              PORTB = 0X01;
	   default:
	      break;
	};
}

int main(void) {
     /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        DDRB = 0XFF;
        PORTB = 0x00; // Initialize PORTB output to 0’s

    state = OffRelease;

    while (1) {
	Tick();	
    }
    return 1;
}
