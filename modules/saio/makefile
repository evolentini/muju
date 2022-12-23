# Variable with module root foder
FOLDER = modules/saio

# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER))))

# Variable with the list of folders containing header files for the module
$(NAME)_INC = $(FOLDER)/inc $(FOLDER)/soc/$(SOC)/src

# Variable with the list of folders containing source files for the module
$(NAME)_SRC = $(FOLDER)/src $(FOLDER)/soc/$(SOC)/src

PROJECT_INC += modules/saio/inc
