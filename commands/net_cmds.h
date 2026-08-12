#ifndef NET_CMDS_H
#define NET_CMDS_H

#include "../vga.h"

void cmd_ip() { print("1: lo: <LOOPBACK,UP> mtu 65536 inet 127.0.0.1/8\n"); }
void cmd_ping() { print("PING 127.0.0.1: 56 bytes of data. 0% packet loss.\n"); }
void cmd_netstat() { print("Active Internet connections: 0 (Standalone Mode)\n"); }
void cmd_dns() { print("Nameserver: 8.8.8.8 (Virtual Gateway)\n"); }

#endif