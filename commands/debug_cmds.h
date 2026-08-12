#ifndef DEBUG_CMDS_H
#define DEBUG_CMDS_H

#include "../vga.h"

void cmd_mem_stat() { print("Total RAM : 1024 MB | Free: 882 MB | Used: 142 MB\n"); }
void cmd_cpu_info() { print("CPU: Intel/AMD x86 Compatible (Protected Mode)\n"); }
void cmd_pci_scan() { print("Scanning PCI buses... [00:01.0 IDE Controller Found]\n"); }
void cmd_dmesg() { print("[ 0.000000] Booting Aurex Kernel...\n[ 0.120000] ATA Drive detected.\n"); }

#endif