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

enum States {Start, Init, HashPress, HashRelease, Unlock, Lock} state;

void Tick(){

	switch(state){
	case Start:
	   state = Init;
	   break;
	case Init:
	   if(PINA == 0x04){ state = HashPress; }
           else{ state = Init; }
	   break;	
	case HashPress:
	   if(PINA == 0x00){ state = HashRelease; }
           else{ state = Init; }
           break;	   	
	case HashRelease:
           if(PINA == 0x02){ state = Unlock; }
	   else{ state = Init; }
           break; 
	case Unlock:
           if((PINA & 0x80) == 0x80){ state = Lock; }
 	   else { state = Unlock; }
           break;
	case Lock:
	   state = Init;
	   break;
 
	default:
	   break;
	};

	   switch(state){
           case Start:
              break;
           case Init:
              break;
           case HashPress:
               break;
           case HashRelease:
               break;
           case Unlock:
              if(PORTB == 0x00){ PORTB = 0x01; }
	      else if(PORTB == 0x01){ PORTB = 0x00; }
              break;
           case Lock:
              PORTB = 0x00;
              break;
           default:
              break;
        };


}

int main(void) {
     /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        DDRB = 0xFF;
        PORTB = 0x01; // Initialize PORTB output to 0’s

    state = Start;

    while (1) {
	Tick();	
    }
    return 1;
}
