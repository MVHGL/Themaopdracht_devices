# settings for Arduino Due projects
TARGET            := arduino_due
SERIAL_PORT       ?= COM2
CONSOLE_BAUDRATE  := 2400
STACK_SIZE        ?= 81920
HEAP              ?= BMPTK

# add the RTOS
RTOS              ?= ./lib/rtos
include           $(RTOS)/makefile.inc

# defer to the Makefile.shared
include           Makefile.shared

# source files in this project (main.cpp is always included)
SOURCES := ir_transmitter.cpp ir_receiver.cpp

#header files in this project
HEADERS := ir_transmitter.hpp ir_receiver.hpp

# PATHS to find files to compile
SEARCH := ./src ./lib ./include
