######################################################################################################
# File name:   Lib.mk
# Description: make file for static library (Unix OS)
#
######################################################################################################


##################################################
# constants
cOS                     :=  $(shell uname -s)

cBUILD_TYPE_DEBUG		:=	debug
cBUILD_TYPE_RELEASE		:=	release

cBIN_TYPE_LIB			:=	static library
cBIN_TYPE_TESTS			:=	tests

cDESCRIPTION 			:=	C++ class library

cCOMPILER				:=	$(CXX)
cARCHIVER				:=	$(AR)


##################################################
# Settings
#BUILD_TYPE				:=	$(cBUILD_TYPE_DEBUG)
BUILD_TYPE				:=	$(cBUILD_TYPE_RELEASE)
BIN_TYPE				:=	$(cBIN_TYPE_LIB)


##################################################
# xLib
ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
PROGRAM_PREFIX			:=	lib
PROGRAM_SHORT_NAME		:=	xlib
PROGRAM_POSTFIX			:=	
PROGRAM_EXT				:=	.a
else
PROGRAM_PREFIX			:=
PROGRAM_SHORT_NAME		:=	xlib
PROGRAM_POSTFIX			:=
PROGRAM_EXT				:=	
endif

PROGRAM_NAME			:=	$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_POSTFIX)$(PROGRAM_EXT)

DIR_ROOT_INCLUDE		:=	./Include
DIR_ROOT_SOURCE			:=	./Source

DIR_OTHER_INCLUDE		:=	#/usr/include \
							#/usr/local/include

SUBDIRS_SOURCE			:=	. \
							Common \
							Common/Win \
							Crypt \
							Crypt/OpenSSL \
							Crypt/Pkcs11 \
							Db \
							Debug \
							Filesystem \
							Gui \
							Gui/Dialogs \
							Gui/Win \
							Gui/Win/Dialogs \
							Gui/Win/GDI+ \
							Log \
							Net \
							Patterns \
							Sync \
							Sync/Win \
                            Test \
							Units \
							Units/Win

DIRS_LIB				:=	/usr/lib64 \
							/usr/lib \
							/usr/lib64/mysql \
							/usr/lib/mysql \
							/usr/local/lib64 \
							/usr/local/lib \
							/usr/local/lib64/mysql \
							/usr/local/lib/mysql

DIR_BINARY				:=	./Library/G++_linux/Release
DIR_INSTALL_INCLUDE		:=	/usr/local/include
DIR_INSTALL				:=	/usr/local/lib
PROGRAM_PATH			:=	../../../$(DIR_BINARY)/$(PROGRAM_NAME)

COMPILER				:=	$(CXX)
ARCHIVER				:=	$(AR)
FLAGS_COMPILE			:=	$(CPPFLAGS) -Wall -pipe

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
FLAGS_LINK				:=	-pthread -s -pipe -O0 -g3 -g -fexceptions
else
FLAGS_LINK				:=	-pthread -s -pipe -O3 -g0 -fomit-frame-pointer -fexceptions
endif

FLAGS_PARANOID			:=	-pedantic -Wall -Wextra -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default \
							-Wswitch-enum -Wsync-nand -Wstrict-overflow=1 -Wstrict-overflow=2 -Wstrict-overflow=3 \
							-Wstrict-overflow=4 -Wstrict-overflow=5 -Wfloat-equal -Wtraditional -Wtraditional-conversion \
							-Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wtype-limits \
							-Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
							-Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-declaration \
							-Wold-style-definition -Wmissing-prototypes  -Wmissing-declarations \
							-Wmissing-field-initializers -Wmissing-format-attribute -Wpacked -Wpadded \
							-Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wvariadic-macros -Wvla \
							-Wvolatile-register-var -Wdisabled-optimization -Wpointer-sign -Wstack-protector

DIRS_RELATIVE_INCLUDE	:=	$(addprefix ../../../, $(DIR_ROOT_INCLUDE))
DIRS_RELATIVE_SOURCE	:=	$(addprefix ../../../$(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
DIRS_OBJECTS			:=	$(addprefix $(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
OBJECTS					:=	$(patsubst ../../../%, %, $(wildcard $(addsuffix /*.cpp, $(DIRS_RELATIVE_SOURCE))))
OBJECTS					:=	$(OBJECTS:.cpp=.o)


$(PROGRAM_PATH):		OBJ_DIRS $(OBJECTS)
						$(ARCHIVER) rc $@ $(OBJECTS)

OBJ_DIRS:
						mkdir -p $(DIRS_OBJECTS)

VPATH					:= ../../../

%.o:					%.cpp
						$(COMPILER) -c $(FLAGS_COMPILE) $(FLAGS_LINK) $(addprefix -I, $(DIRS_RELATIVE_INCLUDE) $(DIR_OTHER_INCLUDE)) -o $@ $<


# targets
all:
						mkdir -p $(DIR_BINARY)
						$(MAKE) --directory=./$(DIR_BINARY) --makefile=../../../Lib.mk

install:
						mkdir -p $(DIR_INSTALL)
						cp    $(DIR_BINARY)/$(PROGRAM_NAME) $(DIR_INSTALL)/$(PROGRAM_NAME)

						mkdir -p $(DIR_INSTALL_INCLUDE)
						cp -r $(DIR_ROOT_INCLUDE)/xLib $(DIR_INSTALL_INCLUDE)

.PHONY:					clean
clean:
						rm -rf $(DIR_BINARY)

include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))

