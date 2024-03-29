MUJU := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
include $(MUJU)/externals/gmsl/gmsl

###############################################################################
# Defintion of project name based on project paths if it was not defined in 
# project makefile, used to define binary file and default target
ifneq ($(PROJECT), )
    -include $(PROJECT)/makefile
    PROJECT_NAME ?= $(lastword $(subst /, , $(PROJECT)))
else
    PROJECT = .
    PROJECT_NAME ?= $(lastword $(subst /, , $(CURDIR)))
endif

PROJECT_DIR = $(abspath $(PROJECT))

###############################################################################
# Function to generate the full path of directory
define full_path
$(strip \
    $(if $(wildcard $(abspath $1)), $(abspath $1), \
        $(if $(wildcard $(PROJECT_DIR)/$1),$(PROJECT_DIR)/$1,$(MUJU)/$1) \
    )
)
endef

###############################################################################
# Function to generate the short path of directory 
define short_path
$(strip \
    $(subst $(abspath $(MUJU))/,,$(subst $(abspath $(PROJECT_DIR))/,,$(abspath $1)))
)
endef

###############################################################################
# Function to generate the compilation parameters with the list of include paths
define include_directories
$(strip \
    $(foreach path,$(sort $1 $(PROJECT_INC)),-I $(call full_path,$(path)))
)
endef

###############################################################################
# Function to generate the compilation parameters with the list of include paths
define defines_list
$(strip \
    $(foreach define,$(DEFINES),-D $(define))
)
endef

###############################################################################
# Function to obtain the last directory of a path
define lastdir
$(strip \
    $(strip $(lastword $(subst /, ,$1)))
)
endef

###############################################################################
# Function to generate the list of object files from a path list
define objects_list
$(strip \
    $(foreach path,$1,
        $(eval SOURCE_DIR = $(call full_path,$(path))) \
        $(eval OBJECT_DIR = $(OBJ_DIR)/$(call short_path,$(path))) \
        $(patsubst $(SOURCE_DIR)/%.$2,$(OBJECT_DIR)/%.o,$(wildcard $(SOURCE_DIR)/*.$2)) \
    )
)
endef

###############################################################################
# Dynamic rule to compile single folder with c source files
define c_compiler_rule
    $(info Definiendo regla de compilacion para $1/*.c en $3)
$3/%.o: $(call full_path,$1)/%.c
	@echo ===============================================================================
	-@mkdir -p $$(@D)
	$$(CC) $$(strip $$(CFLAGS) $$(call defines_list) $$(call include_directories,$2)) -MMD -c $$< -o $$@
endef

###############################################################################
# Dynamic rule to compile single folder with s source files
define assembler_rule
    $(info Definiendo regla de compilacion para $1/*.s en $3)
$3/%.o: $(call full_path,$1)/%.s
	@echo ===============================================================================
	-@mkdir -p $$(@D)
	$$(CC) $$(strip $$(CFLAGS) $$(call defines_list) $$(call include_directories,$2)) -MMD -c $$< -o $$@
endef

###############################################################################
# Dynamic rule to link static library file from module with source code
define library_link_rule
    $(info Definiendo regla de enlazar $(LIB_DIR)/$1.a)
PROJECT_LIB += $(LIB_DIR)/$1.a
$(LIB_DIR)/$1.a: $$($2_OBJ)
	@echo ===============================================================================
	-@mkdir -p $$(@D)
	$$(AR) rcs $$@ $$^
endef

###############################################################################
# Procedure to create dynamic rules for a list of folders with source files
define define_compilation_rules
    $(foreach path, $($1_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(path))))
    $(foreach path, $($1_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(path))))
endef

###############################################################################
# Function to analize a path and include the module makefile if it exists
define analize_path
    $(eval path = $(call full_path,$1)) \
    $(info ---------------------------------------------------) \
    $(info Analizando la carpeta $(path)) \
    $(if $(wildcard $(path)/makefile), \
        $(info Incluyendo el makefile de la carpeta $(path)) \
        $(eval include $(path)/makefile) \
    , \
        $(if $(wildcard $(path)/inc),$(eval $2_INC += $(path)/inc)) \
        $(if $(wildcard $(path)/src), \
            $(info Usando el codigo fuente $(path)/src) \
            $(eval $2_SRC += $(path)/src) \
            $(foreach path,$(wildcard $(path)/*),$(eval $(call analize_path,$(path),$2))) \
        ) \
    )
endef

###############################################################################
# Procedure to create dynamic rules to build a static library from module with source code
define define_library_rules
    $(eval NAME = $(if $2,$2,$(call uc,$(subst /,_,$1))))
    $(eval $(call analize_path,$1,$(NAME)))
    $(if $($(NAME)_SRC), \
        $(eval $(NAME)_OBJ += $$(call objects_list,$$($(NAME)_SRC),c,$1)) \
        $(eval PROJECT_INC += $$($(NAME)_INC)) \
        $(eval $(call define_compilation_rules,$(NAME))) \
        $(eval $(call library_link_rule,$1,$(NAME))) \
        $(eval -include $(patsubst %.o,%.d,$($(NAME)_OBJ))) \
    )
endef

###############################################################################
# Definition of directories variables
# out dir
# BUILD_DIR = $(PROJECT_DIR)/build
BUILD_DIR = build
# object dir
OBJ_DIR = $(BUILD_DIR)/obj
# lib dir
LIB_DIR = $(BUILD_DIR)/lib
# bin dir
BIN_DIR = $(BUILD_DIR)/bin
# rtos gen dir
GEN_DIR = $(BUILD_DIR)/gen
# etc dir (configuration dir)
ETC_DIR = $(BUILD_DIR)/etc

###############################################################################
#
ifneq ($(wildcard $(PROJECT_DIR)/src), )
    PROJECT_SRC ?= $(PROJECT_DIR)/src
else
    PROJECT_SRC ?= $(PROJECT_DIR)
endif

ifneq ($(wildcard $(PROJECT_DIR)/inc), )
    PROJECT_INC ?= $(PROJECT_DIR)/inc
else
    PROJECT_INC ?= $(PROJECT_DIR)
endif

###############################################################################
#

-include $(call full_path,boards/$(BOARD)/makefile)

export BOARD
export CPU
export SOC

CPU_PATHS = modules/base/cpu/$(CPU) externals/base/cpu/$(CPU)
SOC_PATHS = modules/base/soc/$(SOC) externals/base/soc/$(SOC)

CPU_INC = $(foreach path,$(CPU_PATHS),$($(call uc,$(subst /,_,$(path)))_INC))
SOC_INC = $(foreach path,$(SOC_PATHS),$($(call uc,$(subst /,_,$(path)))_INC))

MODULES += boards/$(BOARD) $(CPU_PATHS) $(SOC_PATHS)

###############################################################################
# 
$(foreach module,$(MODULES),$(eval $(call define_library_rules,$(module))))

TARGET_NAME ?= $(BIN_DIR)/$(PROJECT_NAME)
LD_TARGET = $(TARGET_NAME).$(LD_EXTENSION)

-include $(patsubst %.o,%.d,$(PROJECT_OBJ))

###############################################################################
PROJECT_OBJ += $(call objects_list,$(PROJECT_SRC),c)
$(foreach path,$(PROJECT_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))
$(foreach path,$(PROJECT_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))

###############################################################################
$(PROJECT_NAME): $(PROJECT_LIB) $(PROJECT_OBJ) 
	@echo ===============================================================================
	-@mkdir -p $(BIN_DIR)
	$(CC) $(strip $(LFLAGS) $(PROJECT_OBJ) $(PROJECT_LIB) $(LIB_PARAMS)) -o $(LD_TARGET)
	-@cp -f $(LD_TARGET) $(BIN_DIR)/project.$(LD_EXTENSION) 
	@echo ' '

.DEFAULT_GOAL := all

all: $(PROJECT_NAME) $(POST_BUILD_TARGETS)

###############################################################################
# 
clean:
	-@rm -r $(BUILD_DIR)

download: $(PROJECT_NAME)
ifeq ($(FLASH_WRITER),)
	$(error Flash write operation is not available for the board $(BOARD))
else
	@$(FLASH_WRITER) $(FLASH_WRITER_FLAGS) $(FLASH_WRITER_COMMANDS)
endif

info:
	@echo =====================================================================================
	@echo Nombre del proyecto: $(PROJECT_NAME)
	@echo Ruta definida para el proyecto: $(PROJECT)
	@echo Ruta absoluta del Proyecto: $(PROJECT_DIR)
	@echo Binario final: $(LD_TARGET)
	@echo -------------------------------------------------------------------------------------
	@echo Modulos: $(MODULES)
	@echo Placa: $(BOARD), $(CPU), $(SOC)
	@echo -------------------------------------------------------------------------------------
	@echo Fuentes: $(PROJECT_SRC)
	@echo Cabeceras: $(PROJECT_INC)
	@echo Objetos: $(PROJECT_OBJ)
	@echo -------------------------------------------------------------------------------------
