/*
 * main.c
 *
 *  Created on: July 9, 2013
 *      Author: Gabrielle Trotter
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



void set_interrupt_pins();


int main (void)
{
	set_interrupt_pins();
	//set all pins in port B as output (1)
	DDRB |= 0xFF;
	while(1)
	{
		PORTB = 0x01;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);


	}
}

void set_interrupt_pins()
{
	DDRD &= 0xFC;     // Clear the PD2 pin
			// PD2 (PCINT0 pin) is now an input

		PORTD |= 0x02;    // turn on the Pull-up
			// PD2 is now an input with pull-up enabled (supposedly)

		// set INT0 edge trigger
			// 0 = low level, 1 = any, 2 = rising, 3 = falling
		EICRA &= 0xF2;
		EICRA |= 0x02;

	    // Turn on INT0
		EIMSK |= (1 << INT0);

		// turn on global interrupts
		sei();
}


//Interrupt service routine for pin INT0
ISR(INT0_vect)
{
	PORTB = 0x00;
	_delay_ms(1000);


}
