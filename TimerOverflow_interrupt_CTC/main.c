/*
 * proj17_TimerOverflow_interrupt_CTC.c
 *
 * Created: 10/01/2025 3:39:07 pm
 * Author : abax5
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Macros for LED control
#define Led_on  PORTB |= (1 << 7)
#define Led_off PORTB &= ~(1 << 7)

volatile uint8_t isr_flag = 0; // ISR flag to indicate when interrupt occurs

// Timer1 Compare Match ISR
ISR(TIMER1_COMPA_vect) 
{
    isr_flag = 1; // Set flag when Timer1 Compare Match occurs
}

// Function prototype
void Led_toggle(void);

int main(void)
{
    // Configure PORTB as output for LED
    DDRB = 0xFF;

    // Configure Timer1 in CTC mode with prescaler 256
    TCCR1B |= (1 << CS12) | (1 << WGM12);

    // Enable Timer1 Compare Match A interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Set Compare Match value for desired frequency (10Hz)
    uint16_t freq = 10;
    OCR1A = (F_CPU / (2 * 256 * freq)) - 1;

    sei(); // Enable global interrupts

    while (1) 
    {
        if (isr_flag == 1) // Check if ISR flag is set
        {
            Led_toggle();
            isr_flag = 0; // Reset flag
        }
    }

    return 0;
}

// LED toggling function
void Led_toggle(void)
{			
    for (uint8_t i = 0; i < 3; i++) // Toggle LED 3 times
    {
        Led_on;
        _delay_ms(10);
        Led_off;
        _delay_ms(10);
    }
}
