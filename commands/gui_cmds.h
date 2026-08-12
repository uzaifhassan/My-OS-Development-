#ifndef GUI_CMDS_H
#define GUI_CMDS_H

#include "../vga.h"

void cmd_gui() { print("Switching to Graphical Desktop Environment...\n"); }
void cmd_desktop() { print("Desktop status: ONLINE [Aurex Shell v1.0]\n"); }
void cmd_window() { print("Active Window: Aurex Terminal Instance 1\n"); }

#endif