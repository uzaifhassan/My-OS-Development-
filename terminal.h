#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "keyboard.h"
#include "desktop.h"
#include "commands/all_commands.h"

// Custom string functions for bare-metal kernel environment
int term_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int term_strncmp(const char* s1, const char* s2, int n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

int starts_with_term(const char* pre, const char* str) {
    return term_strncmp(pre, str, term_strlen(pre)) == 0;
}

void start_terminal() {
    show_desktop();
    print("Type 'help' to view commands.\n\n");

    char cmd_buffer[256];
    int cmd_index = 0;

    // Initialize buffer cleanly
    for(int i = 0; i < 256; i++) {
        cmd_buffer[i] = 0;
    }

    print("aurex-terminal$ ");

    while (1) {
        char c = get_char();

        if (c == '\n') {
            print("\n");
            cmd_buffer[cmd_index] = '\0';

            // Command Routing
            if (strcmp(cmd_buffer, "help") == 0) { cmd_sys_help(); }
            else if (strcmp(cmd_buffer, "help file") == 0) { cmd_help_file(); }
            else if (strcmp(cmd_buffer, "help sto") == 0) { cmd_help_storage(); }
            else if (strcmp(cmd_buffer, "help sys") == 0) { cmd_help_sys(); }
            else if (strcmp(cmd_buffer, "help proc") == 0) { cmd_help_proc(); }
            else if (strcmp(cmd_buffer, "help net") == 0) { cmd_help_net(); }
            else if (strcmp(cmd_buffer, "help user") == 0) { cmd_help_user(); }
            else if (strcmp(cmd_buffer, "help perm") == 0) { cmd_help_perm(); }
            else if (strcmp(cmd_buffer, "help pkg") == 0) { cmd_help_pkg(); }
            else if (strcmp(cmd_buffer, "help dev") == 0) { cmd_help_dev(); }
            else if (strcmp(cmd_buffer, "help gui") == 0) { cmd_help_gui(); }
            else if (strcmp(cmd_buffer, "help aurex") == 0) { cmd_help_aurex(); }
            else if (strcmp(cmd_buffer, "help debug") == 0) { cmd_help_debug(); }
            else if (strcmp(cmd_buffer, "clear") == 0) { 
                clear_screen(); 
                start_terminal(); 
                return; 
            }
            else if (starts_with_term("cd ", cmd_buffer)) { cmd_cd(&cmd_buffer[3]); }
            else if (strcmp(cmd_buffer, "cd") == 0) { cmd_cd(""); }
            else if (starts_with_term("mkdir ", cmd_buffer)) { cmd_mkdir(&cmd_buffer[6]); }
            else if (starts_with_term("rmdir ", cmd_buffer)) { cmd_rmdir(&cmd_buffer[6]); }
            else if (starts_with_term("touch ", cmd_buffer)) { cmd_touch(&cmd_buffer[6]); }
            else if (starts_with_term("cat ", cmd_buffer)) { cmd_cat(&cmd_buffer[4]); }
            else if (starts_with_term("rm ", cmd_buffer)) { cmd_rm(&cmd_buffer[3]); }
            else if (starts_with_term("cp ", cmd_buffer)) { cmd_cp(&cmd_buffer[3]); }
            else if (starts_with_term("mv ", cmd_buffer)) { cmd_mv(&cmd_buffer[3]); }
            else if (strcmp(cmd_buffer, "tree") == 0) { cmd_tree(); }
            
            // Storage Commands
            else if (strcmp(cmd_buffer, "disk") == 0) { cmd_disk(); }
            else if (strcmp(cmd_buffer, "df") == 0) { cmd_df(); }
            else if (strcmp(cmd_buffer, "du") == 0) { cmd_du(); }
            else if (strcmp(cmd_buffer, "mount") == 0) { cmd_mount(); }
            else if (strcmp(cmd_buffer, "umount") == 0) { cmd_umount(); }
            else if (strcmp(cmd_buffer, "format") == 0) { cmd_format(); }
            else if (strcmp(cmd_buffer, "partition") == 0) { cmd_partition(); }
            else if (strcmp(cmd_buffer, "volumes") == 0) { cmd_volumes(); }

            // System & Info Commands
            else if (strcmp(cmd_buffer, "version") == 0) { cmd_version(); }
            else if (strcmp(cmd_buffer, "uname") == 0) { cmd_uname(); }
            else if (strcmp(cmd_buffer, "hostname") == 0) { cmd_hostname(); }
            else if (strcmp(cmd_buffer, "uptime") == 0) { cmd_uptime(); }
            else if (strcmp(cmd_buffer, "date") == 0) { cmd_date(); }
            else if (strcmp(cmd_buffer, "time") == 0) { cmd_time(); }

            // Process Commands
            else if (strcmp(cmd_buffer, "ps") == 0) { cmd_ps(); }
            else if (strcmp(cmd_buffer, "top") == 0) { cmd_top(); }
            else if (starts_with_term("kill ", cmd_buffer)) { cmd_kill(&cmd_buffer[5]); }
            else if (strcmp(cmd_buffer, "jobs") == 0) { cmd_jobs(); }

            // Network Commands
            else if (strcmp(cmd_buffer, "ip") == 0) { cmd_ip(); }
            else if (strcmp(cmd_buffer, "ping") == 0) { cmd_ping(); }
            else if (strcmp(cmd_buffer, "netstat") == 0) { cmd_netstat(); }
            else if (strcmp(cmd_buffer, "dns") == 0) { cmd_dns(); }

            // User & Permissions Commands
            else if (strcmp(cmd_buffer, "whoami") == 0) { cmd_whoami(); }
            else if (strcmp(cmd_buffer, "users") == 0) { cmd_users(); }
            else if (starts_with_term("adduser ", cmd_buffer)) { cmd_adduser(&cmd_buffer[8]); }
            else if (strcmp(cmd_buffer, "passwd") == 0) { cmd_passwd(); }
            else if (strcmp(cmd_buffer, "chmod") == 0) { cmd_chmod(); }
            else if (strcmp(cmd_buffer, "chown") == 0) { cmd_chown(); }
            else if (strcmp(cmd_buffer, "groups") == 0) { cmd_groups(); }
            else if (strcmp(cmd_buffer, "sudo") == 0) { cmd_sudo(); }

            // Package Commands
            else if (starts_with_term("pkg install ", cmd_buffer)) { cmd_pkg_install(&cmd_buffer[12]); }
            else if (starts_with_term("pkg search ", cmd_buffer)) { cmd_pkg_search(&cmd_buffer[11]); }
            else if (strcmp(cmd_buffer, "pkg update") == 0) { cmd_pkg_update(); }

            // Development Commands
            else if (strcmp(cmd_buffer, "gcc") == 0) { cmd_gcc(); }
            else if (strcmp(cmd_buffer, "make") == 0) { cmd_make(); }
            else if (strcmp(cmd_buffer, "nasm") == 0) { cmd_nasm(); }
            else if (strcmp(cmd_buffer, "compile") == 0) { cmd_compile(); }

            // GUI Commands
            else if (strcmp(cmd_buffer, "gui") == 0) { cmd_gui(); }
            else if (strcmp(cmd_buffer, "desktop") == 0) { cmd_desktop(); }
            else if (strcmp(cmd_buffer, "window") == 0) { cmd_window(); }

            // Aurex Special Commands
            else if (strcmp(cmd_buffer, "aurex") == 0 || strcmp(cmd_buffer, "sysinfo") == 0 || strcmp(cmd_buffer, "about") == 0) { cmd_aurex_info(); }
            else if (strcmp(cmd_buffer, "neofetch") == 0 || strcmp(cmd_buffer, "fetch") == 0) { cmd_neofetch(); }

            // Debugging Commands
            else if (strcmp(cmd_buffer, "mem") == 0 || strcmp(cmd_buffer, "memory") == 0) { cmd_mem_stat(); }
            else if (strcmp(cmd_buffer, "cpu") == 0) { cmd_cpu_info(); }
            else if (strcmp(cmd_buffer, "pci") == 0) { cmd_pci_scan(); }
            else if (strcmp(cmd_buffer, "dmesg") == 0) { cmd_dmesg(); }

            // Utility
            else if (starts_with_term("echo ", cmd_buffer)) {
                print(&cmd_buffer[5]);
                print("\n");
            }
            else if (strcmp(cmd_buffer, "reboot") == 0) {
                outb(0x64, 0xFE);
            }
            else if (strcmp(cmd_buffer, "shutdown") == 0 || strcmp(cmd_buffer, "poweroff") == 0) {
                print("Shutting down Aurex OS...\n");
                outw(0x604, 0x2000);
            }
            else if (strcmp(cmd_buffer, "exit") == 0) {
                print("Session terminated. Halting CPU.\n");
                while(1) { __asm__ __volatile__("hlt"); }
            }
            else if (cmd_buffer[0] != '\0') {
                print("Command not recognized. Type 'help'.\n");
            }

            // Reset Buffer safely
            cmd_index = 0;
            for(int i = 0; i < 256; i++) {
                cmd_buffer[i] = 0;
            }
            print("aurex-terminal$ ");
        } 
        else if (c == '\b') {
            if (cmd_index > 0) {
                cmd_index--;
                cmd_buffer[cmd_index] = 0;
                print("\b \b");
            }
        } 
        else if (c != 0) {
            if (cmd_index < 254) { // Leave room for null terminator
                cmd_buffer[cmd_index++] = c;
                char s[2] = {c, '\0'};
                print(s);
            }
        }
    }
}

#endif