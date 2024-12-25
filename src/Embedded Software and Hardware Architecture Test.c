/*
 * ========================================
 * Educational Example: Timer Configuration
 * ========================================
 * This program is a simplified, illustrative example
 * designed to demonstrate the configuration of peripheral
 * registers (e.g., Timer A0) in a microcontroller-like
 * environment.
 *
 * Note:
 * - This is not intended for actual hardware implementation.
 * - The register simulation uses variables to mimic hardware
 *   registers for demonstration purposes.
 * - Modify the code as necessary for use with real hardware
 *   or specific microcontroller platforms.
 *
 * Purpose:
 * - To teach how to configure registers using bitwise operations.
 * - To demonstrate memory-mapped I/O concepts in embedded systems.
 */

#include <stdio.h>
#include <stdint.h>

// Simulated memory-mapped register for Timer A0 Control
volatile uint16_t TA0CTL = 0x0000; // Simulating Timer A0 Control Register

// Bit masks for the TA0CTL register (Timer A0 Control Register)
#define TASSEL_MASK  0x0300  // Bits 8-9: Timer source select
#define ID_MASK      0x00C0  // Bits 6-7: Input divider
#define MC_MASK      0x0030  // Bits 4-5: Mode control
#define TACLR_MASK   0x0004  // Bit 2: Timer clear
#define TAIE_MASK    0x0002  // Bit 1: Timer interrupt enable
#define TAIFG_MASK   0x0001  // Bit 0: Timer interrupt flag

void configureTimerA0(uint8_t tasel, uint8_t divider, uint8_t mode, uint8_t enableInterrupt) {
    /*
     * This function configures the Timer A0 control register (TA0CTL).
     * Parameters:
     * - tasel: Timer source selection (0-3)
     * - divider: Input divider (0-3)
     * - mode: Timer mode control (0-3)
     * - enableInterrupt: 1 to enable interrupts, 0 to disable.
     */

    // Clear the TA0CTL register
    TA0CTL = 0x0000;

    // Configure the TASSEL (Timer Source Selection)
    TA0CTL |= (tasel << 8) & TASSEL_MASK;

    // Configure the ID (Input Divider)
    TA0CTL |= (divider << 6) & ID_MASK;

    // Configure the MC (Mode Control)
    TA0CTL |= (mode << 4) & MC_MASK;

    // Enable or disable interrupts
    if (enableInterrupt) {
        TA0CTL |= TAIE_MASK; // Enable interrupt
    }

    // Clear the timer (TACLR)
    TA0CTL |= TACLR_MASK;
}

void printTA0CTL() {
    /*
     * This function prints the current configuration of the TA0CTL register.
     * It is intended for debugging and educational purposes.
     */
    printf("TA0CTL Register: 0x%04X\n", TA0CTL);
    printf("Timer Source Select (TASSEL): %d\n", (TA0CTL & TASSEL_MASK) >> 8);
    printf("Input Divider (ID): %d\n", (TA0CTL & ID_MASK) >> 6);
    printf("Mode Control (MC): %d\n", (TA0CTL & MC_MASK) >> 4);
    printf("Timer Clear (TACLR): %s\n", (TA0CTL & TACLR_MASK) ? "Enabled" : "Disabled");
    printf("Interrupt Enable (TAIE): %s\n", (TA0CTL & TAIE_MASK) ? "Enabled" : "Disabled");
    printf("Interrupt Flag (TAIFG): %s\n", (TA0CTL & TAIFG_MASK) ? "Set" : "Clear");
}

int main() {
    // Initial configuration of Timer A0
    printf("=== Initial Timer A0 Configuration ===\n");
    printTA0CTL();

    // Configure Timer A0 with specific settings
    printf("\n=== Configuring Timer A0 ===\n");
    configureTimerA0(2, 1, 2, 1); // TASSEL=2, Divider=1, Mode=2, Interrupt=Enabled

    // Print the updated configuration
    printf("\n=== Updated Timer A0 Configuration ===\n");
    printTA0CTL();

    return 0;
}
