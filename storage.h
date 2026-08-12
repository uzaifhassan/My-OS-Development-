#ifndef STORAGE_H
#define STORAGE_H

unsigned short inw(unsigned short port) {
    unsigned short result;
    __asm__ __volatile__("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void io_wait() {
    outb(0x80, 0x00);
}

void sleep(int count) {
    for (volatile int i = 0; i < count * 300000; i++) {
        __asm__ __volatile__("nop");
    }
}

typedef struct {
    int id;
    char* bus_name;
    unsigned int size_mb;
    int is_present;
} RealDisk;

RealDisk detected_disks[4];
int total_real_disks = 0;

unsigned int probe_ata_drive(unsigned short io_port, unsigned char drive_sel) {
    outb(io_port + 6, drive_sel);
    io_wait();
    outb(io_port + 2, 0);
    outb(io_port + 3, 0);
    outb(io_port + 4, 0);
    outb(io_port + 5, 0);
    outb(io_port + 7, 0xEC); 
    io_wait();

    unsigned char status = inb(io_port + 7);
    if (status == 0) return 0;

    int timeout = 100000;
    while ((status & 0x80) && --timeout > 0) {
        status = inb(io_port + 7);
        if (status & 0x1 || status & 0x20) return 0;
    }
    if (timeout == 0) return 0;

    status = inb(io_port + 7);
    if (!(status & 0x08)) return 0;

    unsigned short target_data[256];
    for (int i = 0; i < 256; i++) {
        target_data[i] = inw(io_port);
    }

    unsigned int sectors = (target_data[61] << 16) | target_data[60];
    unsigned int size_in_mb = (sectors * 512) / (1024 * 1024);
    return size_in_mb;
}

void scan_real_hardware_disks() {
    total_real_disks = 0;
    unsigned int size1 = probe_ata_drive(0x1F0, 0xA0);
    if (size1 > 0) {
        detected_disks[total_real_disks++] = (RealDisk){1, "Primary Master (ATA Controller 0x1F0)", size1, 1};
    }
}

void ata_read_sector(unsigned short io_port, unsigned int lba, unsigned char* target_buf) {
    outb(io_port + 6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(io_port + 2, 1);
    outb(io_port + 3, (unsigned char)lba);
    outb(io_port + 4, (unsigned char)(lba >> 8));
    outb(io_port + 5, (unsigned char)(lba >> 16));
    outb(io_port + 7, 0x20);

    int timeout = 100000;
    while ((inb(io_port + 7) & 0x80) && --timeout > 0);
    if (timeout == 0) return;

    timeout = 100000;
    while (!(inb(io_port + 7) & 0x08) && --timeout > 0);
    if (timeout == 0) return;

    unsigned short* ptr = (unsigned short*)target_buf;
    for (int i = 0; i < 256; i++) {
        ptr[i] = inw(io_port);
    }
}

void ata_write_sector(unsigned short io_port, unsigned int lba, unsigned char* source_buf) {
    outb(io_port + 6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(io_port + 2, 1);
    outb(io_port + 3, (unsigned char)lba);
    outb(io_port + 4, (unsigned char)(lba >> 8));
    outb(io_port + 5, (unsigned char)(lba >> 16));
    outb(io_port + 7, 0x30);

    int timeout = 100000;
    while ((inb(io_port + 7) & 0x80) && --timeout > 0);
    if (timeout == 0) return;

    timeout = 100000;
    while (!(inb(io_port + 7) & 0x08) && --timeout > 0);
    if (timeout == 0) return;

    unsigned short* ptr = (unsigned short*)source_buf;
    for (int i = 0; i < 256; i++) {
        outw(io_port, ptr[i]);
    }
    outb(io_port + 7, 0xE7);
    
    timeout = 100000;
    while ((inb(io_port + 7) & 0x80) && --timeout > 0);
}

#endif