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
SOURCES := ../lasertag/ir_transmitter.cpp initGame.cpp initDisplayTask.cpp initKeypadTask.cpp

# header files in this project
HEADERS := hwlib.hpp ../lasertag/ir_transmitter.hpp initGame.hpp initDisplayTask.hpp initKeypadTask.hpp

# other places to look for files for this project
SEARCH  :=

# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
