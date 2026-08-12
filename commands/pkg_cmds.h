#ifndef PKG_CMDS_H
#define PKG_CMDS_H

#include "../vga.h"

void cmd_pkg_install(char* pkg) { print("Installing package: "); print(pkg); print(" ... Done!\n"); }
void cmd_pkg_search(char* pkg) { print("Found package in Aurex Repository: "); print(pkg); print("\n"); }
void cmd_pkg_update() { print("Package repository synchronized.\n"); }

#endif