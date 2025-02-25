/*
 * proj19_PWM_using_timers.c
 *
 * Created: 28/01/2025 3:48:42 pm
 * Author : abax5
 * This code implements PWM using timers, allowing for PWM generation on pins other than the standard PWM output pins.
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(TIMER1_COMPA_vect) 
{
    PORTC |= (1 << PORTC0); 
}


ISR(TIMER1_COMPB_vect)
{
    PORTC &= ~(1 << PORTC0); 
}


ISR(TIMER0_COMPA_vect)
{
    uint16_t Period = OCR1A;
    OCR1B += 1; 

    // Reset OCR1B if it exceeds the period
    if (OCR1B >= Period)
    {
        OCR1B = 0;
    }
}

// Function to initialize Timer1 for PWM generation
void PWM_Init(void)
{
	//Set prescaler and CTC mode, Enable interrupt for OCR1A and OCR1B
    TCCR1B |= (1 << CS10) | (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); 
}

// Function to set the PWM duty cycle
void PWM_Duty(uint8_t TimeVal)
{
    TCCR0A |= (1 << WGM01); // Set Timer0 to CTC mode
    TCCR0B |= (1 << CS02) | (1 << CS00); // Set prescaler
    TIMSK0 |= (1 << OCIE0A); // Enable Timer0 output compare interrupt
    OCR0A = TimeVal * 7812.5 - 1; // Calculate OCR0A value based on TimeVal
}

int main(void)
{
    DDRC = 0xFF; // Set PORTC as output
    PORTC &= 0xFF; // Initialize PORTC to low

    OCR1A = 800; // Set initial value for OCR1A
    OCR1B = 20; // Set initial value for OCR1B
    sei(); // Enable global interrupts

    PWM_Init(); // Initialize PWM
    PWM_Duty(2); // Set PWM duty cycle

    while (1)
    {
        // Main loop does nothing pwm generation handled by interrupts
    }
}
