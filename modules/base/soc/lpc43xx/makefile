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

# Preprosesor flags
DEFINES += CORE_M4

# Compiler flags
CFLAGS += -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb

# Library builder flags
AFLAGS += -ggdb3 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb

# Linker flags
LFLAGS += -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp

# define linker extension
LD_EXTENSION = elf

# Generates a .bin image file
BIN_TARGET = $(TARGET_NAME).bin
POST_BUILD += arm-none-eabi-objcopy -v -O binary $(LD_TARGET) $(BIN_TARGET)


# Binary name for OpenOCD download target
OPENOCD_BIN 		   = openocd
# Command flags for OpenOCD download target
FLASH_WRITER_FLAGS = -f $(MUJU)/externals/base/soc/$(SOC)/openocd/lpc4337_new.cfg
# Flash base address for OpenOCD download target
FLASH_BASE_ADDRESS := 0x1A000000
# Flash commandfor OpenOCD download target
FLASH_WRITER_COMMANDS = -c "init" -c "halt 0" -c "flash write_image erase $(BIN_TARGET) $(FLASH_BASE_ADDRESS) bin" -c "reset run" -c "shutdown"
