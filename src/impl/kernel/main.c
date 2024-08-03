#include "print.h"

void kernel_main(void) {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("OS version 0.0.1");
    
}
