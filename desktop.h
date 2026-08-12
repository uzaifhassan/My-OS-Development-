#ifndef DESKTOP_H
#define DESKTOP_H

#include "vga.h"

void show_desktop() {
    clear_screen();
    print("================================================================================");
    print(" AUREX OS v1.0 Desktop Environment                          Status: ONLINE    \n");
    print("================================================================================");
    print(" Desktop Icons:  [1] Terminal (Active)   [2] File System   [3] Settings\n");
    print("--------------------------------------------------------------------------------\n\n");
}

#endif