#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "keyboard.h"
#include "storage.h"

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

#endif