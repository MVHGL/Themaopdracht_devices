#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := ir_transmitter.cpp ir_receiver.cpp  ir_decoder.cpp mainGameControlTask.cpp gameTimeControl.cpp time.cpp displayTask.cpp playerData.cpp TriggerTask.cpp registerGameControl.cpp keypadTask.cpp networkControl.cpp

# header files in this project
HEADERS := ir_transmitter.hpp ir_receiver.hpp ir_decoder.hpp mainGameControlTask.hpp gameTimeControl.hpp time.hpp displayTask.hpp playerData.hpp TriggerTask.hpp registerGameControl.hpp keypadTask.hpp networkControl.hpp

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
