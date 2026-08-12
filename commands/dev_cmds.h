#ifndef DEV_CMDS_H
#define DEV_CMDS_H

#include "../vga.h"

void cmd_gcc() { print("aurex-gcc: no input files specified\n"); }
void cmd_make() { print("make: Nothing to be done for 'all'.\n"); }
void cmd_nasm() { print("nasm: assembly completed successfully.\n"); }
void cmd_compile() { print("Source compiled into raw binary successfully.\n"); }

#endif