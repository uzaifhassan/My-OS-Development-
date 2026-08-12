#ifndef FILE_CMDS_H
#define FILE_CMDS_H

#include "../vga.h"

void cmd_pwd() { print("/root/aurex\n"); }
void cmd_ls() { print("bin/  boot/  dev/  etc/  home/  kernel.bin  readme.txt\n"); }
void cmd_cd(char* path) { print("Directory changed to: "); print(path[0] ? path : "/root"); print("\n"); }
void cmd_mkdir(char* name) { print("Directory created: "); print(name); print("\n"); }
void cmd_rmdir(char* name) { print("Directory removed: "); print(name); print("\n"); }
void cmd_touch(char* name) { print("File created: "); print(name); print("\n"); }
void cmd_rm(char* name) { print("File removed: "); print(name); print("\n"); }
void cmd_cp(char* args) { print("Copied successfully: "); print(args); print("\n"); }
void cmd_mv(char* args) { print("Moved/Renamed successfully: "); print(args); print("\n"); }
void cmd_cat(char* file) { 
    if(strcmp(file, "readme.txt") == 0) print("Welcome to AUREX OS v1.0 - Built From the Core.\n");
    else { print("cat: "); print(file); print(": No such file\n"); }
}
void cmd_tree() { print("/\n|-- bin/\n|-- home/\n|-- boot/\n"); }
void cmd_file_mgmt(char* cmd) { print("File Management Action Executed: "); print(cmd); print("\n"); }

#endif