include externals/gmsl/gmsl

###############################################################################
# Function to generate the compilation parameters with the list of include paths
define include_directories
    $(foreach file,$1,-I $(file))
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
# Dynamic rule to create a directory in output structu
define create_directory_rule
    $(info Definiendo regla para crear la carpeta $1 en $2)
$1: $2
	@echo ===============================================================================
	@echo Creando directorio $$@
	-@mkdir -p $$@
endef

###############################################################################
# Dynamic rule to compile single folder with c source files
define c_compiler_rule
    $(info Definiendo regla de compilacion para $1 en $(OBJ_DIR)/$1)
$(OBJ_DIR)/$1/%.o: $(OBJ_DIR)/$1 $1/%.c
	@echo ===============================================================================
	$(CC) $(strip $(CFLAGS) $(call include_directories,$2)) -MMD -c $$(word 2,$$^) -o $$@
endef

###############################################################################
# Dynamic rule to compile single folder with s source files
define assembler_rule
    $(info Definiendo regla de compilacion para $1 en $(OBJ_DIR)/$1)
$(OBJ_DIR)/$1/%.o: $(OBJ_DIR)/$1 $1/%.s
	@echo ===============================================================================
	$(CC) $(strip $(CFLAGS) $(call include_directories,$2)) -MMD -c $$(word 2,$$^) -o $$@
endef

###############################################################################
# Dynamic rule to link static library file from module with source code
define library_link_rule
    $(info Definiendo regla de enlazar $(LIB_DIR)/$1.a)
PROJECT_LIB += $(LIB_DIR)/$1.a
$(LIB_DIR)/$1.a: $(dir $(LIB_DIR)/$1.a) $$($2_OBJ)
	@echo ===============================================================================
	$(AR) rcs $$@ $$(filter %.o,$$^)
endef

###############################################################################
# Procedure to create dynamic rules for a list of folders with source files
define define_compilation_rules
    $(foreach path, $($1_SRC),$(eval $(call create_directory_rule,$(OBJ_DIR)/$(path),$(OBJ_DIR))))
    $(foreach path, $($1_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(path))))
    $(foreach path, $($1_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(path))))
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
# Procedure to create a dynamic rules to build folder for static library file if its necesary
define define_library_folder_rule
    $(if $(findstring $1,$(DEFINED_FOLDERS)), \
        $(info Ya existe una regla definida para crear el directorio $1) \
    , \
        $(info Definiendo una nueva regla para crear el directorio $1) \
        $(eval DEFINED_FOLDERS += $1)
        $(eval $(call create_directory_rule,$1,$2)) \
    )
endef

###############################################################################
# Procedure to create dynamic rules to build a static library from module with source code
define define_library_rules
    $(eval NAME = $(call uc,$(subst /,_,$1)))
    $(eval $(call analize_path,$1,$(NAME)))
    $(if $($(NAME)_SRC), \
        $(eval $(NAME)_OBJ = $$(call objects_list,$$($(NAME)_SRC),c,$1)) \
        $(eval PROJECT_INC += $$($(NAME)_INC)) \
        $(eval $(call define_library_folder_rule,$(dir $(LIB_DIR)/$1.a),$(LIB_DIR))) \
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

BUILD_FOLDERS = obj lib bin

DIR_LIST = OBJ_DIR LIB_DIR BIN_DIR GEN_DIR ETC_DIR

$(eval $(call create_directory_rule,$(BUILD_DIR),$(ROOT_DIR)))
$(foreach path,$(DIR_LIST),$(eval $(call create_directory_rule,$($(path)),$(BUILD_DIR))))

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
export BOARD
export CPU
export SOC

MODULES += boards/$(BOARD)/makefile
MODULES += modules/base/cpu/$(CPU) modules/base/soc/$(SOC)
MODULES += externals/base/cpu/$(CPU) externals/base/soc/$(SOC)

###############################################################################
# 
$(foreach module,$(MODULES),$(eval $(call define_library_rules,$(module))))

TARGET_NAME ?= $(BIN_DIR)/$(PROJECT_NAME)
LD_TARGET = $(TARGET_NAME).$(LD_EXTENSION)

-include $(patsubst %.o,%.d,$(PROJECT_OBJ))

PROJECT_OBJ += $(call objects_list,$(PROJECT_SRC),c)
$(eval $(call define_compilation_rules,PROJECT))
$(PROJECT_NAME): $(BIN_DIR) $(PROJECT_LIB) $(PROJECT_OBJ) 
	@echo ===============================================================================
	$(CC) $(strip $(LFLAGS) $(PROJECT_OBJ) $(PROJECT_LIB) $(LIB_PARAMS)) -o $(LD_TARGET) 
	@echo ' '

.DEFAULT_GOAL := $(PROJECT_NAME)

###############################################################################
# 
clean: $(BUILD_DIR)
	-@rm -r $(BUILD_DIR)

info:
	@echo Proyecto: $(PROJECT)
	@echo Modulos: $(MODULES)
	@echo Placa: $(BOARD), $(CPU), $(SOC)