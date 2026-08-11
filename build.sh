#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "=========================================="
echo "       BUILDING UZAIF OS (CLI v1.0)       "
echo "=========================================="

# 1. Assembly compile karein (Standard ELF32 format for Linux)
echo "[1/5] Compiling boot.asm..."
nasm -f elf32 boot.asm -o boot.o

# 2. C Kernel compile karein
echo "[2/5] Compiling kernel.c..."
gcc -m32 -c kernel.c -o kernel.o -ffreestanding -fno-pie -fno-stack-protector -fno-builtin

# 3. Link karein (Using linker.ld script)
echo "[3/5] Linking object files into binary..."
ld -m elf_i386 -T linker.ld -o my_os.bin boot.o kernel.o

# 4. ISO structure prepare karein
echo "[4/5] Preparing ISO directory structure..."
mkdir -p iso/boot/grub
cp my_os.bin iso/boot/my_os.bin

if [ -f "grub.cfg" ]; then
    cp grub.cfg iso/boot/grub/grub.cfg
else
    echo "Error: grub.cfg not found! Please create grub.cfg first."
    exit 1
fi

# 5. Bootable ISO Image banayein
echo "[5/5] Generating bootable ISO image..."
grub-mkrescue -o uzaif_os.iso iso

echo "=========================================="
echo " Build Successful! ISO created: uzaif_os.iso"
echo "=========================================="