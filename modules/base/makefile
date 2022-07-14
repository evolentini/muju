include externals/gmsl/gmsl

###############################################################################
# Function to generate the compilation parameters with the list of include paths
define include_directories
    $(foreach file,$(sort $1 $(PROJECT_INC)),-I $(file))
endef

###############################################################################
# Function to generate the compilation parameters with the list of include paths
define defines_list
    $(foreach define,$(DEFINES),-D $(define))
endef

###############################################################################
# Function to obtain the last directory of a path
define lastdir
    $(strip $(lastword $(subst /, ,$1)))
endef

###############################################################################
# Function to generate the list of object files from a path list
define objects_list
    $(foreach path,$1,$(patsubst $(path)/%.$2,$(OBJ_DIR)/$(path)/%.o,$(wildcard $(path)/*.$2)))
endef

###############################################################################
# Dynamic rule to compile single folder with c source files
define c_compiler_rule
    $(info Definiendo regla de compilacion para $1/*.c en $3)
$3/%.o: $1/%.c
	@echo ===============================================================================
	-@mkdir -p $$(@D)
	$$(CC) $$(strip $$(CFLAGS) $$(call defines_list) $$(call include_directories,$2)) -MMD -c $$< -o $$@
endef

###############################################################################
# Dynamic rule to compile single folder with s source files
define assembler_rule
    $(info Definiendo regla de compilacion para $1/*.s en $3)
$3/%.o: $1/%.s
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
    $(info ---------------------------------------------------) \
    $(if $(wildcard $1/makefile), \
        $(info Incluyendo el makefile de la carpeta $1) \
        $(eval include $1/makefile) \
    , \
        $(if $(wildcard $1/inc),$(eval $2_INC += $1/inc)) \
        $(if $(wildcard $1/src), \
            $(info Usando el codigo fuente $1/src) \
            $(eval $2_SRC += $1/src) \
            $(foreach path,$(wildcard $1/*),$(eval $(call analize_path,$(path),$2))) \
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
ROOT_DIR := .
# out dir
BUILD_DIR = $(ROOT_DIR)/build
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
# Defintion of project name based on project paths if it was not defined in 
# project makefile, used to define binary file and default target
ifneq ($(PROJECT), )
    -include $(PROJECT)/makefile
    PROJECT_NAME ?= $(lastword $(subst /, , $(PROJECT)))
else
    PROJECT = .
    PROJECT_NAME ?= $(lastword $(subst /, , $(CURDIR)))
endif

ifneq ($(wildcard $(PROJECT)/src), )
    PROJECT_SRC ?= $(PROJECT)/src
else
    PROJECT_SRC ?= $(PROJECT)
endif

ifneq ($(wildcard $(PROJECT)/inc), )
    PROJECT_INC ?= $(PROJECT)/inc
else
    PROJECT_INC ?= $(PROJECT)
endif

###############################################################################
#

-include boards/$(BOARD)/makefile

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
PROJECT_OBJ := $(foreach path,$(PROJECT_OBJ),$(subst $(PROJECT),$(PROJECT_NAME),$(path)))
$(foreach path, $(PROJECT_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(subst $(PROJECT),$(OBJ_DIR)/$(PROJECT_NAME),$(path)))))
$(foreach path, $(PROJECT_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(subst $(PROJECT),$(OBJ_DIR)/$(PROJECT_NAME),$(path)))))

###############################################################################
$(PROJECT_NAME): $(PROJECT_LIB) $(PROJECT_OBJ) 
	@echo ===============================================================================
	-@mkdir -p $(BIN_DIR)
	$(CC) $(strip $(LFLAGS) $(PROJECT_OBJ) $(PROJECT_LIB) $(LIB_PARAMS)) -o $(LD_TARGET)
	-@cp -f $(LD_TARGET) $(BIN_DIR)/project.$(LD_EXTENSION) 
	@echo ' '

.DEFAULT_GOAL := $(PROJECT_NAME)

###############################################################################
# 
clean:
	-@rm -r $(BUILD_DIR)

NAMES = $(foreach path,$(CPU_PATHS),$(call uc,$(subst /,_,$(path)))_INC)
DEBUG = $(foreach path,$(CPU_PATHS),$($(call uc,$(subst /,_,$(path)))_INC))
DEBUG = $(foreach path,$(PROJECT_OBJ),$(patsubst $(PROJECT),$(OBJ_DIR)/%.o,$(path)))
DEBUG = $(foreach path,$(PROJECT_OBJ),$(subst $(PROJECT),$(PROJECT_NAME),$(path)))

info:
	@echo Proyecto: $(PROJECT)
	@echo Modulos: $(MODULES)
	@echo Placa: $(BOARD), $(CPU), $(SOC)
	@echo Debug: $(DEBUG)
	@echo Values: $(NAMES)
	@echo Objetos: $(PROJECT_OBJ)
	@echo Rutas con cabeceras del CPU: $(CPU_INC)
	@echo Rutas con cabeceras del SOC: $(SOC_INC)
	@echo Demo: $(EXTERNALS_BASE_CPU_ARM-THUMB_INC)