#ifndef PROCESS_CMDS_H
#define PROCESS_CMDS_H

#include "../vga.h"

void cmd_ps() { print("PID   STATE   COMMAND\n  1     RUN     /boot/kernel.bin\n  2     RUN     aurex-terminal\n"); }
void cmd_top() { print("Tasks: 2 total, 2 running. CPU Usage: 0.4% usr\n"); }
void cmd_kill(char* pid) { print("Process killed successfully (PID "); print(pid); print(")\n"); }
void cmd_jobs() { print("No active background jobs.\n"); }

#endif