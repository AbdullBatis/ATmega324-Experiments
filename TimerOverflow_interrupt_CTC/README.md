# Timer Overflow Interrupt in CTC Mode Project

## Description
This project uses Timer1 in CTC mode on the ATmega324 to toggle an LED at 10 Hz. The LED is controlled by a flag set in the Timer1 Compare Match Interrupt Service Routine (ISR).
Utilizes Timer1 in CTC mode to achieve precise timing without blocking code execution. The LED is toggled in the main loop based on the flag set in the ISR, ensuring responsiveness.






