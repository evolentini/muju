# MODULES = modules/hal modules/freertos
MODULES = modules/hal
BOARD ?= edu-ciaa-nxp
# PROJECT ?= projects/demo
PROJECT ?= examples/demo_hal

include modules/base/makefile
