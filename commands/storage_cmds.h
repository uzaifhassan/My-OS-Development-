#ifndef STORAGE_CMDS_H
#define STORAGE_CMDS_H

#include "../vga.h"

void cmd_disk() { print("Disk: Primary Master ATA (10240 MB) - Active\n"); }
void cmd_df() { print("Filesystem     1K-blocks      Used Available Use% Mounted on\n/dev/hda1        1048576    145000    903576  14% /\n"); }
void cmd_du() { print("145MB   /root/aurex\n"); }
void cmd_mount() { print("Mounted /dev/hda1 on / type ext2 (rw)\n"); }
void cmd_umount() { print("Unmounted successfully.\n"); }
void cmd_format() { print("Formatting target storage partition...\n"); }
void cmd_partition() { print("Active Partitions: [1] Primary Bootable (10GB)\n"); }
void cmd_volumes() { print("Available Volumes: Volume_C (Aurex Root)\n"); }

#endif