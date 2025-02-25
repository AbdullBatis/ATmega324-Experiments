/*
 * proj13_ADC.c
 * Analog-to-Digital Conversion (ADC) with LCD Display
 * Created: 12/12/2024 10:03:20 PM
 * Author : abax5
 */

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTD

//Defining the control pins in the LCD
#define en PE4
#define rw PE3
#define rs PE2

void Init_LCD(void);
void LCD_cmd(unsigned char com);
void LCD_write(unsigned char data);
void Cursor_pos(unsigned char x_pos, unsigned char y_pos);
void init_ADC(void);
uint16_t ADC_read(uint8_t channel);

int main(void)
{
    DDRD = 0xFF;  // Configure PORTD as output for LCD data
    DDRE = 0xFF;  // Configure PORTE as output for LCD control signals
    
    Init_LCD();
    init_ADC();
    _delay_ms(100);
    LCD_cmd(0x0C);  // Display ON, cursor OFF
    _delay_ms(100);
    LCD_cmd(0x01);  // Clear screen
    _delay_ms(2);

    // Display "KPAD=" on the first line
    char text1[] = "KPAD=";
    for (int i = 0; text1[i] != '\0'; i++) {
        LCD_write(text1[i]);
        _delay_ms(1);
    }

    LCD_cmd(0xC0);  // Move to the second line command
    _delay_ms(1);
    
    // Display "FINAL=" on the second line
    char text2[] = "FINAL=";
    for (int i = 0; text2[i] != '\0'; i++) {
        LCD_write(text2[i]);
        _delay_ms(1);
    }
    
    char ch[4] = {' '};  // Buffer for ADC value
    uint16_t Data_final;
    
    while (1) 
    {
        Data_final = ADC_read(0);  // Read ADC value from channel 0
        
        // Clear previous data from buffer
        for (int j = 0; j < 4; j++) {
            ch[j] = ' ';
        }
        
        Cursor_pos(0, 8);  // Move cursor to position (0,8)
        itoa(Data_final, ch, 10);  // Convert integer to string
        
        for (int j = 0; j < 4; j++) {
            // Ensure only numeric values are displayed
            if (ch[j] < '0' || ch[j] > '9') {
                LCD_write(' ');
            } else {
                LCD_write(ch[j]);
            }
        }
        _delay_ms(200);
    }
}

void Init_LCD(void)
{
    LCD_cmd(0x38);  // 8-bit mode, 2-line display
    _delay_ms(1);
    LCD_cmd(0x01);  // Clear display
    _delay_ms(1);
    LCD_cmd(0x02);  // Return home
    _delay_ms(1);
    LCD_cmd(0x06);  // Auto-increment cursor
    _delay_ms(1);
    LCD_cmd(0x80);  // Move cursor to the beginning of the first line
    _delay_ms(1);
}

void LCD_cmd(unsigned char com)
{
    LCD_DATA = com;
    PORTE &= ~(1 << rs);  // Command mode
    PORTE &= ~(1 << rw);  // Write mode
    PORTE |= (1 << en);
    _delay_ms(2);
    PORTE &= ~(1 << en);
}

void LCD_write(unsigned char data)
{
    LCD_DATA = data;
    PORTE |= (1 << rs);  // Data mode
    PORTE &= ~(1 << rw);  // Write mode
    PORTE |= (1 << en);
    _delay_ms(1);
    PORTE &= ~(1 << en);
}

void Cursor_pos(unsigned char x_pos, unsigned char y_pos)
{
    uint8_t The_Address = (x_pos == 0) ? 0x80 : 0xC0;
    if (y_pos < 16) The_Address += y_pos;
    LCD_cmd(The_Address);
}

void init_ADC(void)
{
    ADMUX |= (1 << REFS0);  // Set reference voltage to AVCC
    ADCSRA |= (1 << ADEN);  // Enable ADC
    ADCSRA |= (1 << ADSC);  // Start conversion
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));  // Set prescaler to 128
}

uint16_t ADC_read(uint8_t channel)
{
	//single conversion mode
    ADMUX &= 0xF0;  // clear previous channel selection
    ADMUX |= channel;  // Select new channel
    ADCSRA |= (1 << ADSC);  // Start new conversion
    while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
    return ADC;  // Return ADC result
}
