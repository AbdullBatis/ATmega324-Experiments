/*
 * proj4_7Segments.c
 *
 * Created: 6/10/2024 12:29:43 pm
 * Author : abax5
 */ 

#define F_CPU 16000000UL // 16 MHz crystal clock

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN (1 << PINB0) 

int main(void)
{
	 // Set PORTD as output low
	DDRD = 0b11111111;
	PORTD = 0b00000000; 

	// Set PORTB as input (button) with pullups enabled
	DDRB = 0b00000000; 
	PORTB = 0b11111111;

	uint8_t x = 0; 
	uint8_t segments[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Segment values for 0-9

	while (1)
	{
		
		if (PINB & BUTTON_PIN)
		{
			_delay_ms(50); // Debounce delay
			if (x < 9) 
			{
				x++; 
				PORTD = segments[x]; // Update PORTD to display the number
			}
		}

		
		if (x == 10)
		{
			x = 0; // Reset counter
			PORTD = x; 
		}
	}
}