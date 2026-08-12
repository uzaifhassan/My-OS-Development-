#ifndef USER_CMDS_H
#define USER_CMDS_H

#include "../vga.h"

void cmd_whoami() { print("root (Developer: Uzaif Hassan)\n"); }
void cmd_users() { print("Logged-in users: root\n"); }
void cmd_adduser(char* usr) { print("User added: "); print(usr); print("\n"); }
void cmd_passwd() { print("Password updated successfully.\n"); }

#endif