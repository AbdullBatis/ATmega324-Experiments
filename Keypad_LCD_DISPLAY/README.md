# keypad and LCD Display Implementation 

## Description
This project implements a prototype that displays fixed text on a 16x2 LCD while allowing user input from a keypad. The system is designed to test the functionality of the LCD and keypad interface, displaying entered integers on the screen.

## Key Features
- Displays the text "TEMP=" and "SPEED=" on the LCD.
- Allows user input through a keypad, with the entered integers shown on the LCD.
- This code serves as a prototype for testing the LCD and keypad functionalities.

## Components Used
- AVR ATmega324 microcontroller
- 16x2 character LCD
- 4x4 matrix keypad
- Resistors and capacitors as needed for connections

## Circuit Connections
- **LCD**: Connected to PORTD for data and to specific pins on PORTE for control signals.
- **Keypad**: Connected to PORTA for scanning button presses.

## Note
This project does not measure actual temperature or speed, as it is a prototype for testing the interface functionality. Further development is required to connect appropriate sensors for real measurements.
