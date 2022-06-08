# Variable with module root foder
FOLDER = modules/hal

# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER))))

# Variable with the list of folders containing header files for the module
$(NAME)_INC = $(FOLDER)/inc $(FOLDER)/soc/inc

# Variable with the list of folders containing source files for the module
$(NAME)_SRC = $(FOLDER)/src $(FOLDER)/soc/$(SOC)

PROJECT_INC += modules/hal/inc