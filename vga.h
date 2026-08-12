#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned short* vga_buffer = (unsigned short*) VGA_ADDRESS;
int cursor_x = 0, cursor_y = 0;

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = (0x07 << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
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
        if (cursor_y >= VGA_HEIGHT) {
            cursor_y = VGA_HEIGHT - 1; 
        }
        i++;
    }
}

// Custom Color Printing (Attribute byte: High 4 bits background, Low 4 bits foreground)
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
    print("               . . .   A U R E X   O S   . . .                          \n");
    print("                   Slogan: Built From the Core.                         \n");
    print("================================================================================");
}

#endif