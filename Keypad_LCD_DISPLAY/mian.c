/*
 * proj6_Keypad_lcd_display.c
 *
 * Created: 10/11/2024 5:50:06 PM
 * Author : abax5
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTD
#define en PE4
#define rw PE3
#define rs PE2
#define x1 !(1 << PINA6)  // Input from a button 

void Init_LCD(void);
void LCD_cmd(unsigned char com);
void LCD_write(unsigned char data);
void Cursor_pos(unsigned char x_pos, unsigned char y_pos);
char keypad(void);

int main(void)
{
    DDRD = 0xFF;    // Set PORTD as output for LCD data
    DDRE = 0x1C;    // Set PE2, PE3, PE4 as output for LCD control

    DDRA = 0x0F;    // Set lower nibble of PORTA as input for keypad
    PORTA = 0xFF;   // Enable pull-up resistors for PORTA

    Init_LCD();
    _delay_ms(2);
    LCD_cmd(0x0C);  // Display ON, cursor OFF
    _delay_ms(2);
    LCD_cmd(0x01);  // Clear screen
    _delay_ms(2);

    // Display fixed text on the first line
    LCD_write('T');
    _delay_ms(1);
    LCD_write('E');
    _delay_ms(1);
    LCD_write('M');
    _delay_ms(1);
    LCD_write('P');
    _delay_ms(1);
    LCD_write('=');
    _delay_ms(1);
    
    LCD_cmd(0xC0);  // Move to the second line
    _delay_ms(1);
    LCD_cmd(0x0C);  // Display ON, cursor OFF
    _delay_ms(1);

    // Display fixed text on the second line
    LCD_write('S');
    _delay_ms(1);
    LCD_write('P');
    _delay_ms(1);
    LCD_write('E');
    _delay_ms(1);
    LCD_write('D');
    _delay_ms(1);
    LCD_write('=');
    _delay_ms(1);

    while (1) 
    {
        Cursor_pos(1, 6);  // Move cursor to second line, 6th position
        char key = keypad(); // Read key from keypad
        if (key != 'N') // If a key is pressed
        {
            LCD_write(key); // Display the pressed key
            _delay_ms(10);
        }
    }
    return 0;
}

void Init_LCD(void)
{
    LCD_cmd(0x38);  // Set to 8-bit mode
    _delay_ms(1);
    LCD_cmd(0x01);  // Clear display
    _delay_ms(1);
    LCD_cmd(0x02);  // Return home
    _delay_ms(1);
    LCD_cmd(0x06);  // Increment cursor after writing
    _delay_ms(1);
    LCD_cmd(0x80);  // Move cursor to the beginning of the first line
    _delay_ms(1);
}

void LCD_cmd(unsigned char com)
{
    LCD_DATA = com;         // Set data to command
    PORTE &= ~(1 << rs);    // Select command register
    PORTE &= ~(1 << rw);    // Set write mode
    PORTE |= (1 << en);     // Enable the LCD
    _delay_ms(2);           // Wait for the command to be processed
    PORTE &= ~(1 << en);    // Disable the LCD
}

void LCD_write(unsigned char data)
{
    LCD_DATA = data;        // Set data to write
    PORTE |= (1 << rs);     // Select data register
    PORTE &= ~(1 << rw);    // Set write mode
    PORTE |= (1 << en);     // Enable the LCD
    _delay_ms(1);           // Wait for the data to be processed
    PORTE &= ~(1 << en);    // Disable the LCD
}

void Cursor_pos(unsigned char x_pos, unsigned char y_pos)
{
    uint8_t The_Address = 0;
    if (x_pos == 0)
        The_Address = 0x80; // First line
    else if (x_pos == 1)
        The_Address = 0xC0; // Second line

    if (y_pos < 16)        
        The_Address += y_pos;  

    LCD_cmd(The_Address);   // Move cursor to specified position
}

char keypad(void)
{
	// Scan the keypad to detect which button is pressed.
	
	//Set first row to low, then second and so on...
    PORTA = 0xF1;           
    _delay_ms(1);
    if (PINA & 0b00010000) return '1';
    if (PINA & 0b00100000) return '2';
    if (PINA & 0b01000000) return '3';
    if (PINA & 0b10000000) return 'A';

    PORTA = 0xF2;           
    _delay_ms(1);
    if (PINA & 0b00010000) return '4';
    if (PINA & 0b00100000) return '5';
    if (PINA & 0b01000000) return '6';
    if (PINA & 0b10000000) return 'B';
    
    PORTA = 0xF4;           
    _delay_ms(1);
    if (PINA & 0b00010000) return '7';
    if (PINA & 0b00100000) return '8';
    if (PINA & 0b01000000) return '9';
    if (PINA & 0b10000000) return 'C';

    PORTA = 0xF8;           
    _delay_ms(1);
    if (PINA & 0b00010000) return '*';
    if (PINA & 0b00100000) return '0';
    if (PINA & 0b01000000) return '#';
    if (PINA & 0b10000000) return 'D';

    return 'N';             // No key pressed
}
