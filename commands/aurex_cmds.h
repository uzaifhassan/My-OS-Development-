#ifndef AUREX_CMDS_H
#define AUREX_CMDS_H

#include "../vga.h"

void cmd_aurex_info() {
    print("========================================\n");
    print(" AUREX OS - Built From the Core        \n");
    print(" Developer: Uzaif Hassan               \n");
    print(" Architecture: Monolithic x86 Kernel   \n");
    print("========================================\n");
}
void cmd_neofetch() {
    print("       /\\       root@aurex-os\n");
    print("      /  \\      -------------\n");
    print("     / /\\ \\     OS: Aurex OS i386 Bare-Metal\n");
    print("    / /__\\ \\    Kernel: Custom Monolithic\n");
    print("   /_/    \\_\\   Shell: aurex-terminal\n");
}

#endif