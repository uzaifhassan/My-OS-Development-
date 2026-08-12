#ifndef PERM_CMDS_H
#define PERM_CMDS_H

#include "../vga.h"

void cmd_chmod() { print("Permissions modified (chmod 755)\n"); }
void cmd_chown() { print("Owner changed to root:root\n"); }
void cmd_groups() { print("root wheel adm\n"); }
void cmd_sudo() { print("Executing with elevated root privileges...\n"); }

#endif