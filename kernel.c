#include "vga.h"
#include "keyboard.h"
#include "storage.h"
#include "terminal.h"

void show_blue_progress_bar() {
    print("\nInstalling AUREX OS Core Components...\n\n");
    
    print(" [");
    int bar_start_x = cursor_x;
    int bar_start_y = cursor_y;
    
    for (int i = 0; i < 30; i++) {
        print(" ");
    }
    print("]  0%");

    for (int i = 0; i <= 30; i++) {
        cursor_x = bar_start_x;
        cursor_y = bar_start_y;
        
        for (int j = 0; j < i; j++) {
            char block[2] = {(char)219, '\0'};
            print_colored(block, 0x1B);
        }
        
        for (int j = i; j < 30; j++) {
            print(" ");
        }
        
        print("] ");
        int percent = (i * 100) / 30;
        if (percent < 10) print("  ");
        else if (percent < 100) print(" ");
        print_int(percent);
        print("%");

        sleep(100);
    }
    
    // Save Installation Signature ("AUREX_OS") to Sector 1 of Hard Disk
    unsigned char sector_buf[512];
    for(int i=0; i<512; i++) sector_buf[i] = 0;
    char* signature = "AUREX_OS";
    for(int i=0; i<8; i++) sector_buf[i] = signature[i];
    
    ata_write_sector(0x1F0, 1, sector_buf);

    print("\n\nInstallation Completed Successfully!\nPress any key to boot Desktop...");
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
        // Quick Boot Screen with Animated Progress Bar
        print("\n\n\n\n\n\n\n\n");
        print("                        AUREX OS - Booting Core...\n");
        print("                        Slogan: Built From the Core.\n\n");
        
        print("          [");
        int bar_start_x = cursor_x;
        int bar_start_y = cursor_y;
        
        for (int i = 0; i < 30; i++) {
            print(" ");
        }
        print("]  0%");

        for (int i = 0; i <= 30; i++) {
            cursor_x = bar_start_x;
            cursor_y = bar_start_y;
            
            for (int j = 0; j < i; j++) {
                print("=");
            }
            
            for (int j = i; j < 30; j++) {
                print(" ");
            }
            
            print("] ");
            int percent = (i * 100) / 30;
            if (percent < 10) print("  ");
            else if (percent < 100) print(" ");
            print_int(percent);
            print("%");

            sleep(50); // Fast loading speed for quick boot
        }
        
        sleep(150);
        start_desktop();
    } else {
        // First Time Installation Flow
        print("\n\n\n\n\n\n\n\n\n                               Press any key to boot...");
        get_char();

        clear_screen();
        show_aurex_banner();
        
        print("\nScanning Real Hardware Storage Devices (ATA/IDE)...\n");
        scan_real_hardware_disks();
        
        print("\nAvailable Real Disks Found:\n");
        if (total_real_disks > 0) {
            for (int i = 0; i < total_real_disks; i++) {
                print("  [");
                print_int(detected_disks[i].id);
                print("] ");
                print(detected_disks[i].bus_name);
                print(" - Size: ");
                print_int(detected_disks[i].size_mb);
                print(" MB\n");
            }
        } else {
            print("  [1] Primary Master Drive (Virtual Fallback) - Size: 10240 MB\n");
            total_real_disks = 1;
        }

        print("\nSelect Disk Target Number for Installation: ");
        
        char key = '0';
        while (1) {
            key = get_char();
            if (key >= '1' && key <= '1' + total_real_disks - 1) {
                char s[2] = {key, '\0'};
                print(s);
                print("\n");
                break;
            }
        }

        show_blue_progress_bar();
        start_desktop();
    }
}