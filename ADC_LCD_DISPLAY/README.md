# Analog-to-Digital Conversion (ADC) with 16x2 LCD Display Example

## Description
This project implements analog-to-digital conversion (ADC) and displays the converted value on a 16x2 character LCD. The program reads the ADC value from channel 0 and continuously updates the display.

## Key Features
- Displays the text "KPAD=" and "FINAL=" on the 16x2 LCD.
- Continuously reads and displays the ADC value in real-time.
- Utilizes a simple LCD interface for data output.

## ADC Input
- Connect the analog input signal to **ADC0** (PA0 pin).
- **ADC0** is connected to a **10k potentiometer** for varying input voltage.