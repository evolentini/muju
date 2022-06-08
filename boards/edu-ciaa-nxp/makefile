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

CPU        	?= arm-thumb
SOC         ?= lpc43xx
COMPILER    ?= gcc

# Variable with module root foder
FOLDER_BRD = boards/$(BOARD)
FOLDER_CPU = externals/base/cpu/$(CPU)
FOLDER_SOC = externals/base/soc/$(SOC)

# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER_BRD))))

# Variable with the list of folders containing header files for the module
$(NAME)_INC := $(FOLDER_BRD)/inc  $(FOLDER_CPU)/cmsis_core/inc $(FOLDER_SOC)/boards/inc $(FOLDER_SOC)/lpc_chip_43xx/inc 

# Variable with the list of folders containing source files for the module
$(NAME)_SRC := $(FOLDER_BRD)/src $(FOLDER_CPU)/cmsis_core/src $(FOLDER_CPU)/sys_newlib/src $(FOLDER_SOC)/lpc_chip_43xx/src $(FOLDER_SOC)/lpc_startup/src

