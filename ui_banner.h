#ifndef UI_BANNER_H
#define UI_BANNER_H

#include "vga.h"

#define COLOR_WINDOW   0x1F 
#define COLOR_TITLE    0x1E 
#define COLOR_SUCCESS  0x1A 
#define COLOR_ACCENT   0x1B 

// Box drawing function (Added static inline)
static inline void draw_ui_box(int start_x, int start_y, int width, int height, unsigned char color) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cursor_x = start_x + x;
            cursor_y = start_y + y;
            
            char ch = ' ';
            if (y == 0 || y == height - 1) ch = (x == 0 || x == width - 1) ? '+' : '-';
            else if (x == 0 || x == width - 1) ch = '|';
            
            char str[2] = {ch, '\0'};
            print_colored(str, color);
        }
    }
}

// Main Installer Window Container
static inline void draw_installer_window() {
    clear_screen();
    draw_ui_box(5, 1, 70, 23, COLOR_WINDOW);
}

// Clean Triangle Logo & AUREX OS Banner
static inline void render_aurex_logo() {
    cursor_x = 34; cursor_y = 3;
    print_colored(" /\\ ", COLOR_TITLE);
    cursor_x = 33; cursor_y = 4;
    print_colored("/  \\", COLOR_TITLE);
    cursor_x = 32; cursor_y = 5;
    print_colored("/ /\\ \\", COLOR_TITLE);
    cursor_x = 31; cursor_y = 6;
    print_colored("/ /  \\ \\", COLOR_TITLE);
    cursor_x = 30; cursor_y = 7;
    print_colored("/_/__\\_\\", COLOR_TITLE);

    cursor_x = 31; cursor_y = 9;
    print_colored("AUREX OS", COLOR_ACCENT);
    
    cursor_x = 27; cursor_y = 10;
    print_colored("Built From the Core", COLOR_SUCCESS);
}

#endif