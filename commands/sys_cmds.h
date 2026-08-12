#ifndef SYS_CMDS_H
#define SYS_CMDS_H

#include "../vga.h"

void cmd_sys_help() {
    print("=== AUREX OS ALL COMMAND CATEGORIES ===\n");
    print("Use 'help <category>' to view specific commands:\n\n");
    print("  help file   - File Commands & Management\n");
    print("  help sto    - Disk / Storage Commands\n");
    print("  help sys    - System Commands\n");
    print("  help proc   - Process Commands\n");
    print("  help net    - Network Commands\n");
    print("  help user   - User Commands\n");
    print("  help perm   - Permissions Commands\n");
    print("  help pkg    - Package Commands\n");
    print("  help dev    - Development Commands\n");
    print("  help gui    - GUI Commands\n");
    print("  help aurex  - Aurex OS Special Commands\n");
    print("  help debug  - Testing / Debugging Commands\n");
}

void cmd_help_file() {
    print("\n");
    print("=== [1] FILE COMMANDS & MANAGEMENT ===\n");
    print("  pwd, ls, cd, mkdir, rmdir\n");
    print("  touch, rm, cp, mv, cat, tree\n");
}

void cmd_help_storage() {
    print("\n");
    print("=== [2] DISK / STORAGE COMMANDS ===\n");
    print("  disk, df, du, mount, umount\n");
    print("  format, partition, volumes\n");
}

void cmd_help_sys() {
    print("\n");
    print("=== [3] SYSTEM COMMANDS ===\n");
    print("  version, uname, hostname\n");
    print("  uptime, date, time, clear, reboot, shutdown\n");
}

void cmd_help_proc() {
    print("\n");
    print("=== [4] PROCESS COMMANDS ===\n");
    print("  ps, top, kill, jobs\n");
}

void cmd_help_net() {
    print("=== [5] NETWORK COMMANDS ===\n");
    print("  ip, ping, netstat, dns\n");
}

void cmd_help_user() {
    print("\n");
    print("=== [6] USER COMMANDS ===\n");
    print("  whoami, users, adduser, passwd\n");
}

void cmd_help_perm() {
    print("\n");
    print("=== [7] PERMISSIONS COMMANDS ===\n");
    print("  chmod, chown, groups, sudo\n");
}

void cmd_help_pkg() {
    print("\n");
    print("=== [8] PACKAGE COMMANDS ===\n");
    print("  pkg install, pkg search, pkg update\n");
}

void cmd_help_dev() {
    print("\n");
    print("=== [9] DEVELOPMENT COMMANDS ===\n");
    print("  gcc, make, nasm, compile\n");
}

void cmd_help_gui() {
    print("\n");
    print("=== [10] GUI COMMANDS ===\n");
    print("  gui, desktop, window\n");
}

void cmd_help_aurex() {
    print("\n");
    print("=== [11] AUREX OS SPECIAL COMMANDS ===\n");
    print("  aurex, sysinfo, about, neofetch, fetch\n");
}

void cmd_help_debug() {
    print("\n");
    print("=== [12] TESTING / DEBUGGING COMMANDS ===\n");
    print("  mem, memory, cpu, pci, dmesg\n");
}

void cmd_version() { print("Aurex OS v1.0 Stable Release\n"); }
void cmd_uname() { print("AurexOS 1.0-baremetal i386 Monolithic Kernel\n"); }
void cmd_hostname() { print("aurex-host.local\n"); }
void cmd_uptime() { print("Uptime: Active & Stable\n"); }
void cmd_date() { print("Date: 2026-08-12\n"); }
void cmd_time() { print("Time: UTC Synchronized\n"); }

#endif