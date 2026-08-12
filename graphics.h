#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

/* Theme Colors */
#define G_COLOR_WINDOW   0x1F
#define G_COLOR_TITLE    0x1E
#define G_COLOR_SUCCESS  0x1A
#define G_COLOR_ACCENT   0x1B
#define G_COLOR_WHITE    0x0F

/* Draw Box */
static inline void draw_box(int start_x, int start_y, int width, int height, unsigned char color) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cursor_x = start_x + x;
            cursor_y = start_y + y;
            
            char ch = ' ';
            if (y == 0 || y == height - 1) {
                if (x == 0 || x == width - 1) ch = '+';
                else ch = '-';
            } else if (x == 0 || x == width - 1) {
                ch = '|';
            }

            char str[2] = {ch, '\0'};
            print_colored(str, color);
        }
    }
}

/* Filled Upward Triangle */
static inline void draw_triangle(int center_x, int start_y, int height, unsigned char color) {
    for (int row = 0; row < height; row++) {
        int width = (row * 2) + 1;
        int start_x = center_x - row;
        cursor_y = start_y + row;

        for (int x = 0; x < width; x++) {
            cursor_x = start_x + x;
            char block[2] = {(char)219, '\0'};
            print_colored(block, color);
        }
    }
}

/* Center Text Helper */
static inline void draw_center_text(const char* text, int y, unsigned char color) {
    int length = 0;
    while (text[length] != '\0') {
        length++;
    }

    cursor_x = (80 - length) / 2;
    cursor_y = y;
    print_colored(text, color);
}

/* Installer Window Container */
static inline void draw_installer_window() {
    clear_screen();
    draw_box(5, 1, 70, 23, G_COLOR_WINDOW); // Height 23 (rows 1 to 23)
}

/* Render Logo & Default Text */
static inline void render_graphics_logo() {
    // Triangle at top (Height 7, rows 2 to 8)
    draw_triangle(40, 2, 7, G_COLOR_WHITE);

    // Default Subtitles inside box bounds
    draw_center_text("AUREX OS", 11, G_COLOR_ACCENT);
    draw_center_text("Built From the Core", 13, G_COLOR_SUCCESS);
}

#endif