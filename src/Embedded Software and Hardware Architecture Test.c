#include <stdint.h>
#include <stdio.h>

// Hypothetical addresses for GPIO registers as pointers
volatile uint8_t *P1DIR = (volatile uint8_t *)0x40004C00; // Pointer to Port 1 Direction Register
volatile uint8_t *P1OUT = (volatile uint8_t *)0x40004C02; // Pointer to Port 1 Output Register

// Define bit mask for LED_PIN (P1.0)
#define LED_PIN_MASK (uint8_t)(0x01) // Bit 0 mask for P1.0

int main(void)
{
    // 1. Set the direction of the LED pin as output using the bit mask
    *P1DIR |= LED_PIN_MASK; // Configure P1.0 as output

    while (1)
    {
        // 2. Turn the LED ON by setting the output high using the bit mask
        *P1OUT |= LED_PIN_MASK; // Write "1" to turn on the LED
        printf("LED ON\n");    // Print message to indicate LED is ON

        // Delay using a for loop
        for (volatile uint32_t i = 0; i < 100000; i++)
            ; // Empty loop for delay

        // 3. Turn the LED OFF by clearing the output using the bit mask
        *P1OUT &= ~LED_PIN_MASK; // Write "0" to turn off the LED
        printf("LED OFF\n");    // Print message to indicate LED is OFF

        // Delay using a for loop
        for (volatile uint32_t i = 0; i < 100000; i++)
            ; // Empty loop for delay
    }

    return 0; // Optional, but good practice
}

//	LED ON
//	LED OFF
//	LED ON
//	LED OFF
//	...

