#include <stdio.h>
#include <stdint.h>

// Define a control register using bit fields
typedef struct {
    uint8_t enable     : 1;  // 1 bit: Device ON/OFF control (1 = ON, 0 = OFF)
    uint8_t mode       : 2;  // 2 bits: Mode selection (00 = Idle, 01 = Active, 10 = Sleep, 11 = Reserved)
    uint8_t interrupt  : 1;  // 1 bit: Interrupt enable flag (1 = Enabled, 0 = Disabled)
    uint8_t reserved   : 4;  // 4 bits: Reserved (unused), fills up the remaining bits to make a full byte (8 bits total)
} ControlRegister;

int main() {
    // Declare a variable of ControlRegister type, and initialize all bits to 0
    ControlRegister ctrl = {0};

    // Set the 'enable' bit to 1 → This means the device is turned ON
    ctrl.enable = 1;

    // Set the 'mode' bits to 2 → This represents "Sleep mode" (binary 10)
    ctrl.mode = 2;

    // Set the 'interrupt' bit to 1 → This enables interrupt functionality
    ctrl.interrupt = 1;

    // ----- Output the values of each bit field individually -----
    printf("Enable bit value     : %d\n", ctrl.enable);     // Expected output: 1
    printf("Mode bits value      : %d\n", ctrl.mode);       // Expected output: 2
    printf("Interrupt bit value  : %d\n", ctrl.interrupt);  // Expected output: 1

    // ----- Access the full 8-bit value of the entire struct -----
    // Cast the address of 'ctrl' to a pointer to uint8_t to view raw byte value
    uint8_t* rawData = (uint8_t*)&ctrl;

    // Print the full byte as hexadecimal to see how bits are packed
    printf("Raw Register Value (Hex): 0x%02X\n", *rawData);

    // ----- Print the size of the structure in bytes -----
    // This tells us how much memory is allocated for the struct (typically 1 byte here)
    printf("Size of ControlRegister struct: %lu bytes\n", sizeof(ControlRegister));

    return 0;
}


//		Enable bit value     : 1
//		Mode bits value      : 2
//		Interrupt bit value  : 1
//		Raw Register Value (Hex): 0x0D
//		Size of ControlRegister struct: 1 bytes
