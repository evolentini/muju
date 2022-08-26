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

# PROJECT_SRC += externals/base/cpu/arm-thumb/sys_newlib/src

# PROJECT_INC += externals/base/cpu/arm-thumb/cmsis_core/inc
# PROJECT_SRC += externals/base/cpu/arm-thumb/cmsis_core/src


# Variable with module root foder
FOLDER = externals/base/cpu/arm-thumb


# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER))))

# Variable with the list of folders containing header files for the module
# $(NAME)_INC := $(FOLDER)/cmsis_core/inc

# Variable with the list of folders containing source files for the module
# $(NAME)_SRC := $(FOLDER)/cmsis_core/src $(FOLDER)/sys_newlib/src

# Variable with compiler flags required by thi module
DEFINES += __USE_NEWLIB

# Variable with linker flags required by thi module
LFLAGS += -nostartfiles --specs=nano.specs --specs=nosys.specs
