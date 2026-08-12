#include "vga.h"
#include "keyboard.h"
#include "storage.h"
#include "desktop.h"
#include "terminal.h"
#include "graphics.h"

void show_blue_progress_bar(int box_x, int box_y) {
    cursor_x = box_x + 4;
    cursor_y = box_y + 13;
    print_colored("Installing Core Components...", G_COLOR_WINDOW);

    int bar_x = box_x + 4;
    int bar_y = box_y + 15;
    
    cursor_x = bar_x;
    cursor_y = bar_y;
    print_colored(" [", G_COLOR_WINDOW);
    
    int bar_start_x = cursor_x;
    int bar_start_y = cursor_y;
    
    for (int i = 0; i < 30; i++) print(" ");
    print("]   0%");

    for (int i = 0; i <= 30; i++) {
        cursor_x = bar_start_x;
        cursor_y = bar_start_y;
        
        for (int j = 0; j < i; j++) {
            char block[2] = {(char)219, '\0'};
            print_colored(block, G_COLOR_SUCCESS);
        }
        
        for (int j = i; j < 30; j++) {
            print(" ");
        }
        
        print_colored("] ", G_COLOR_WINDOW);
        int percent = (i * 100) / 30;
        if (percent < 10) print("  ");
        else if (percent < 100) print(" ");
        print_int(percent);
        print("%");

        sleep(70);
    }
    
    // Save Installation Signature ("AUREX_OS") to Sector 1 of Hard Disk
    unsigned char sector_buf[512];
    for(int i = 0; i < 512; i++) sector_buf[i] = 0;
    char* signature = "AUREX_OS";
    for(int i = 0; i < 8; i++) sector_buf[i] = signature[i];
    
    ata_write_sector(0x1F0, 1, sector_buf);

    cursor_x = box_x + 4;
    cursor_y = box_y + 18;
    print_colored("[+] Installation Completed Successfully!", G_COLOR_SUCCESS);
    cursor_x = box_x + 4;
    cursor_y = box_y + 20;
    print_colored("Press any key to boot Desktop...", G_COLOR_ACCENT);
    get_char();
}

void k_main() {
    clear_screen();

    // Check if Aurex OS is already installed on the hard disk
    unsigned char sector_buf[512];
    ata_read_sector(0x1F0, 1, sector_buf);

    int is_installed = 1;
    char* signature = "AUREX_OS";
    for (int i = 0; i < 8; i++) {
        if (sector_buf[i] != signature[i]) {
            is_installed = 0;
            break;
        }
    }

    if (is_installed) {
        // --- FAST BOOT SCREEN ---
        draw_box(15, 5, 50, 12, G_COLOR_WINDOW);
        
        cursor_x = 26; cursor_y = 7;
        print_colored("AUREX OS - Booting...", G_COLOR_TITLE);
        cursor_x = 23; cursor_y = 8;
        print_colored("Slogan: Built From the Core.", G_COLOR_ACCENT);

        int bar_x = 20;
        int bar_y = 11;
        cursor_x = bar_x; cursor_y = bar_y;
        print_colored(" [", G_COLOR_WINDOW);
        
        int b_x = cursor_x;
        int b_y = cursor_y;
        for (int i = 0; i < 30; i++) print(" ");
        print("]   0%");

        for (int i = 0; i <= 30; i++) {
            cursor_x = b_x; cursor_y = b_y;
            for (int j = 0; j < i; j++) print_colored("=", G_COLOR_SUCCESS);
            for (int j = i; j < 30; j++) print(" ");
            
            print_colored("] ", G_COLOR_WINDOW);
            int percent = (i * 100) / 30;
            if (percent < 10) print("  ");
            else if (percent < 100) print(" ");
            print_int(percent);
            print("%");
            sleep(40);
        }
        
        sleep(150);
        start_terminal();
    } else {
        // --- STEP 1: WELCOME SCREEN ---
        draw_installer_window();
        
        // Draw Triangle Logo at top (Rows 2 to 8)
        draw_triangle(40, 2, 7, G_COLOR_WHITE);

        // Perfectly spaced text inside the box bounds
        cursor_x = 27; cursor_y = 11;
        print_colored("WELCOME TO AUREX OS SETUP", G_COLOR_TITLE);

        cursor_x = 35; cursor_y = 14;
        print_colored("AUREX OS", G_COLOR_ACCENT);

        cursor_x = 31; cursor_y = 16;
        print_colored("Built From the Core", G_COLOR_SUCCESS);

        cursor_x = 24; cursor_y = 20;
        print_colored("Press any key to continue...", G_COLOR_ACCENT);
        
        get_char();

        // --- STEP 2: HARDWARE DETECTION SCREEN ---
        draw_installer_window();
        draw_triangle(40, 2, 5, G_COLOR_WHITE); // Smaller triangle for space

        cursor_x = 9; cursor_y = 9;
        print_colored("Scanning Real Hardware Storage (ATA/IDE)...", G_COLOR_ACCENT);
        scan_real_hardware_disks();
        
        cursor_x = 9; cursor_y = 11;
        print_colored("Available Real Disks Found:", G_COLOR_TITLE);
        
        int start_row = 13;
        if (total_real_disks > 0) {
            for (int i = 0; i < total_real_disks; i++) {
                cursor_x = 11; cursor_y = start_row + i;
                print("  [");
                print_int(detected_disks[i].id);
                print("] ");
                print(detected_disks[i].bus_name);
                print(" - Size: ");
                print_int(detected_disks[i].size_mb);
                print(" MB");
            }
        } else {
            cursor_x = 11; cursor_y = start_row;
            print("  [1] Primary Master Drive (Virtual Fallback) - Size: 10240 MB");
            total_real_disks = 1;
        }

        // Prompt for Installation Target
        cursor_x = 9; cursor_y = 19;
        print_colored("Select Disk Target Number for Installation: ", G_COLOR_WINDOW);

        char key = '0';
        while (1) {
            key = get_char();
            if (key >= '1' && key <= '1' + total_real_disks - 1) {
                char s[2] = {key, '\0'};
                print_colored(s, G_COLOR_SUCCESS);
                break;
            }
        }

        sleep(500);

        // --- STEP 3: PROGRESS BAR INSTALLATION SCREEN ---
        draw_installer_window();
        draw_triangle(40, 2, 5, G_COLOR_WHITE);

        show_blue_progress_bar(5, 1);
        start_terminal();
    }
}