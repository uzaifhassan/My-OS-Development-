#include "vga.h"
#include "keyboard.h"
#include "storage.h"

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

void start_desktop() {
    clear_screen();
    print("================================================================================");
    print(" AUREX OS v1.0 Desktop Environment                          Status: ONLINE    \n");
    print("================================================================================");
    print(" Desktop Icons:  [1] Terminal (Active)   [2] File System   [3] Settings\n");
    print("--------------------------------------------------------------------------------\n\n");
    
    print("Type 'help' to view commands.\n\n");

    char cmd_buffer[256];
    int cmd_index = 0;

    print("aurex-terminal$ ");

    while (1) {
        char c = get_char();

        if (c == '\n') {
            print("\n");
            cmd_buffer[cmd_index] = '\0';

            if (strcmp(cmd_buffer, "help") == 0) {
                print("Aurex Terminal Commands:\n");
                print("  help     - Show menu\n");
                print("  clear    - Clear desktop console\n");
                print("  sysinfo  - Display Aurex core info\n");
                print("  about    - Detailed system information\n");
                print("  echo     - Print text\n");
                print("  reboot   - Reboot system\n");
                print("  poweroff - Safely shutdown system\n");
            } 
            else if (strcmp(cmd_buffer, "clear") == 0) {
                start_desktop();
                return;
            } 
            else if (strcmp(cmd_buffer, "sysinfo") == 0) {
                print("OS Name: AUREX OS\n");
                print("Tagline: Built From the Core.\n");
                print("Kernel: Bare-Metal x86 Custom Kernel\n");
            } 
            else if (strcmp(cmd_buffer, "about") == 0) {
                print("========================================\n");
                print(" AUREX OS - Architectural Overview     \n");
                print("========================================\n");
                print(" Version    : 1.0 Stable Build          \n");
                print(" Core       : Monolithic Bare-Metal     \n");
                print(" Developer  : Uzaif Hassan              \n");
                print(" Slogan     : Built From the Core.      \n");
                print("========================================\n");
            }
            else if (cmd_buffer[0] == 'e' && cmd_buffer[1] == 'c' && cmd_buffer[2] == 'h' && cmd_buffer[3] == 'o' && cmd_buffer[4] == ' ') {
                print(&cmd_buffer[5]);
                print("\n");
            }
            else if (strcmp(cmd_buffer, "reboot") == 0) {
                outb(0x64, 0xFE);
            }
            else if (strcmp(cmd_buffer, "poweroff") == 0) {
                print("Shutting down Aurex OS...\n");
                outw(0x604, 0x2000);
            }
            else if (cmd_buffer[0] != '\0') {
                print("Command not recognized. Type 'help'.\n");
            }

            cmd_index = 0;
            for(int i=0; i<256; i++) cmd_buffer[i] = 0;
            print("aurex-terminal$ ");
        } 
        else if (c == '\b') {
            if (cmd_index > 0) {
                cmd_index--;
                print("\b \b");
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

void k_main() {
    clear_screen();

    // 1. Check if Aurex OS is already installed on the hard disk
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
        // Quick Boot Screen (Skipping Installer)
        print("\n\n\n\n\n\n\n\n");
        print("                        AUREX OS - Booting Core...\n");
        print("                        Slogan: Built From the Core.\n\n");
        
        // Quick loading animation
        print("          [==============================] 100%\n");
        sleep(400);
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