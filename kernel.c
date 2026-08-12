// VGA Buffer Constants
#define VGA_ADDRESS 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned short* vga_buffer = (unsigned short*) VGA_ADDRESS;
int cursor_x = 0, cursor_y = 0;

// Basic Port IO for keyboard and system control
unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ __volatile__("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(unsigned short port, unsigned char data) {
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}

// Clear Screen
void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = (0x07 << 8) | ' '; // Light grey on black
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

// Print String to Screen
void print(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            const int index = cursor_y * VGA_WIDTH + cursor_x;
            vga_buffer[index] = (0x07 << 8) | str[i];
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        if (cursor_y >= VGA_HEIGHT) {
            // Simple scroll simulation: reset to top or handle scroll
            cursor_y = 0; 
        }
        i++;
    }
}

// US Keyboard Scan-code to ASCII mapping (Basic lowercase)
unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

// Read character from PS/2 Keyboard (Fixed check: inb(0x64) & 1)
char get_char() {
    while (1) {
        if (inb(0x64) & 1) { // Check if keyboard buffer has data properly
            unsigned char scancode = inb(0x60);
            if (scancode < 128) {
                return keyboard_map[scancode];
            }
        }
    }
}

// String Comparison
int strcmp(char* s1, char* s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') return 0;
        i++;
    }
    return s1[i] - s2[i];
}

// Main OS Entry Point
void k_main() {
    clear_screen();
    print("==================================================\n");
    print("                   Aurex OS                       \n");
    print("==================================================\n");
    print("Type 'help' to see available commands.\n\n");

    char cmd_buffer[256];
    int cmd_index = 0;

    print("uzaif-os> ");

    while (1) {
        char c = get_char();

        if (c == '\n') {
            print("\n");
            cmd_buffer[cmd_index] = '\0';

            // Command Processing
            if (strcmp(cmd_buffer, "help") == 0) {
                print("Available Commands:\n");
                print("  help     - Show this help menu\n");
                print("  clear    - Clear screen\n");
                print("  sysinfo  - Display OS version details\n");
                print("  echo     - Print text (e.g. echo Hello)\n");
                print("  reboot   - Restart system\n");
            } 
            else if (strcmp(cmd_buffer, "clear") == 0) {
                clear_screen();
            } 
            else if (strcmp(cmd_buffer, "sysinfo") == 0) {
                print("OS Name: Aurex OS\n");
                print("Architecture: x86 (32-bit Bare-metal)\n");
                print("Kernel: C + Assembly\n");
                print("Developer: Uzaif\n");
            } 
            else if (cmd_buffer[0] == 'e' && cmd_buffer[1] == 'c' && cmd_buffer[2] == 'h' && cmd_buffer[3] == 'o' && cmd_buffer[4] == ' ') {
                print(&cmd_buffer[5]);
                print("\n");
            }
            else if (strcmp(cmd_buffer, "reboot") == 0) {
                // Pulse CPU reset line via keyboard controller
                outb(0x64, 0xFE);
            }
            else if (cmd_buffer[0] != '\0') {
                print("Unknown command. Type 'help'.\n");
            }

            // Reset buffer and show prompt again
            cmd_index = 0;
            for(int i=0; i<256; i++) cmd_buffer[i] = 0;
            print("Aurex OS> ");
        } 
        else if (c == '\b') {
            if (cmd_index > 0) {
                cmd_index--;
                print("\b \b"); // Backspace effect on screen
            }
        } 
        else if (c != 0) {
            if (cmd_index < 255) {
                cmd_buffer[cmd_index++] = c;
                char s[2] = {c, '\0'};
                print(s);
            }
        }
    }
}