#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned short* vga_buffer = (unsigned short*) VGA_ADDRESS;
int cursor_x = 0, cursor_y = 0;

// Outb function prototype declaration
void outb(unsigned short port, unsigned char data);

// Scroll screen upwards by 1 line when reaching the bottom
void scroll_screen() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
        }
    }
    // Clear the last line
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (0x07 << 8) | ' ';
    }
}

void clear_screen() {
    char* vga = (char*) 0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga[i] = ' ';     // Character
        vga[i+1] = 0x07;  // Attribute (Light grey on black)
    }
    
    cursor_x = 0;
    cursor_y = 0;

    // Direct VGA Hardware Cursor Reset
    unsigned short pos = 0;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

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
        
        // Check if cursor exceeds screen height, trigger scrolling
        if (cursor_y >= VGA_HEIGHT) {
            scroll_screen();
            cursor_y = VGA_HEIGHT - 1;
        }
        i++;
    }
}

// Custom Color Printing with scrolling support
void print_colored(char* str, unsigned char color) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            const int index = cursor_y * VGA_WIDTH + cursor_x;
            vga_buffer[index] = (color << 8) | str[i];
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        
        if (cursor_y >= VGA_HEIGHT) {
            scroll_screen();
            cursor_y = VGA_HEIGHT - 1;
        }
        i++;
    }
}

void print_int(int num) {
    char str[16];
    int i = 0;
    if (num == 0) {
        print("0");
        return;
    }
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = temp;
    }
    str[i] = '\0';
    print(str);
}

void show_aurex_banner() {
    print("================================================================================");
    print("              . . .   A U R E X   O S   . . .                                   \n");
    print("                    Slogan: Built From the Core.                                \n");
    print("================================================================================");
}

#endif