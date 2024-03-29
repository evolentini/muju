###############################################################################
#
# Copyright 2022, Esteban Volentini - Facet UNT
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

# Preprocesor command
PP = gcc
# C compiler command
CC = gcc
# Library builder command
AR = ar
# Linker command
LD = gcc
# Assembler command
AS = as
# Debbuger command
GDB = gdb
# ??
NM = nm

# Preprocesor definitions
DEFINES += BOARD=$(BOARD) CPU=$(CPU) SOC=$(SOC)

# Compiler flags
CFLAGS += -c -Wall -ggdb3 -fdata-sections -ffunction-sections

# Library builder flags
AFLAGS += -ggdb3

# Linker flags
# LFLAGS += -Wl,-Map="$(TARGET_NAME).map",-gc-sections

# Debugger flags
# GDB_FLAGS = $(LD_TARGET) -ex "target remote localhost:3333"

#,-print-gc-sections
# Optional POST BUILD
# Generates a .bin image file
# POST_BUILD += arm-none-eabi-objcopy -v -O binary $(LD_TARGET) $(TARGET_NAME).bin

# define linker extension
LD_EXTENSION = out
