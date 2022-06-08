# Variable with module root foder
FOLDER = externals/freertos

DEFINES = USE_FREERTOS

# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER))))

ifeq ($(BOARD),posix)
    PORT := $(FOLDER)/portable/ThirdParty/GCC/Posix $(FOLDER)/portable/ThirdParty/GCC/Posix/utils
    $(NAME)_OBJ += $(OBJ_DIR)/$(FOLDER)/portable/MemMang/heap_3.o
else
    PORT = $(FOLDER)/portable/GCC/ARM_CM4F
    $(NAME)_OBJ += $(OBJ_DIR)/$(FOLDER)/portable/MemMang/heap_4.o
endif

# Variable with the list of folders containing header files for the module
$(NAME)_INC := $(FOLDER)/include $(PORT) $(PROJECT_INC) boards/$(BOARD)/inc

# Variable with the list of folders containing source files for the module
$(NAME)_SRC := $(FOLDER) $(PORT)

$(eval $(call c_compiler_rule,$(FOLDER)/portable/MemMang,$(NAME)_INC))

