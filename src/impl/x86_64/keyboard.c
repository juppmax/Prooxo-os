#include <stdint.h>
#include "io.h"
#include "print.h"

char scancode_to_ascii[128] = {
    0,   27, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', 'ß', '\'', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'z',
    'u', 'i', 'o', 'p', 'ü', '+', '\n',
    0,   'a', 's', 'd', 'f', 'g', 'h',
    'j', 'k', 'l', 'ö', 'ä', '#', 0,
    '<', 'y', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '-', 0,  0,  0,
    ' '
};

char scancode_to_char(uint8_t scancode) {
    if (scancode < 128) { // only handle valid scancodes 
        return scancode_to_ascii[scancode];
    }
    return -1; //Return -1 for invalid or unsupported scancodes
}

uint8_t poll_keyboard() {
    //read status register (0x64)
    if (inb(0x64) & 0x1) {
        //data is available so read it from 0x60
        return inb(0x60);
    }
    return 0;
}

void keyboard_loop() {
    int i = 1;
    while (i < 0) {
        uint8_t scancode = poll_keyboard();
        if (scancode != 0) { //if a scancode is available
            char character = scancode_to_char(scancode);

            if (character != 0) {
                print_char(character);
            }
        }
    }
}