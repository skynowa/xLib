######################################################################################################
# File name:   Lib.mk
# Description: make file for static library (Unix OS)
#
######################################################################################################


##################################################
# constants
cBUILD_TYPE_DEBUG		:=	debug
cBUILD_TYPE_RELEASE		:=	release

cBIN_TYPE_LIB			:=	static library
cBIN_TYPE_TESTS			:=	tests

cDESCRIPTION 			:=	C++ class library


##################################################
# Settings
BUILD_TYPE				:=	$(cBUILD_TYPE_RELEASE)
BIN_TYPE				:=	$(cBIN_TYPE_LIB)


##################################################
# xLib
ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
PROGRAM_PREFIX			:=	lib
PROGRAM_EXT				:=	.a
else
PROGRAM_PREFIX			:=
PROGRAM_EXT				:=
endif

PROGRAM_NAME			:=	$(PROGRAM_PREFIX)xlib$(PROGRAM_EXT)

ROOT_INCLUDE_DIR		:=	./Include
ROOT_SOURCE_DIR			:=	./Source

OTHER_INCLUDE_DIR		:=	/usr/include \
							/usr/local/include

SOURCE_SUBDIRS			:=	. \
							Common \
							Common/Win \
							Crypt \
							Crypt/OpenSSL \
							Crypt/Pkcs11/Win \
							Db \
							Debug \
							Filesystem \
							Filesystem/Win \
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
							Units \
							Units/Win

LIB_DIRS				:=	/usr/lib64 \
							/usr/lib \
							/usr/lib64/mysql \
							/usr/lib/mysql \
							/usr/local/lib64 \
							/usr/local/lib \
							/usr/local/lib64/mysql \
							/usr/local/lib/mysql

BINARY_DIR				:=	./Library/G++_linux/Release
INSTALL_INCLUDE_DIR		:=	/usr/local/include/xLib
INSTALL_DIR				:=	/usr/local/lib/xLib
PROGRAM_PATH			:=	../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER				:=	$(CXX)
ARCHIVER				:=	$(AR)
COMPILE_FLAGS			:=	-Wall -pipe
LINK_FLAGS				:=	-pthread -s -pipe

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BUILD_FLAGS				:=	-O0 -g3 -g
else
BUILD_FLAGS				:=	-O3 -g0
endif

PARANOID_FLAGS			:=	-pedantic -Wall -Wextra -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default \
							-Wswitch-enum -Wsync-nand -Wstrict-overflow=1 -Wstrict-overflow=2 -Wstrict-overflow=3 \
							-Wstrict-overflow=4 -Wstrict-overflow=5 -Wfloat-equal -Wtraditional -Wtraditional-conversion \
							-Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wtype-limits \
							-Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
							-Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-declaration \
							-Wold-style-definition -Wmissing-prototypes  -Wmissing-declarations \
							-Wmissing-field-initializers -Wmissing-format-attribute -Wpacked -Wpadded \
							-Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wvariadic-macros -Wvla \
							-Wvolatile-register-var -Wdisabled-optimization -Wpointer-sign -Wstack-protector

RELATIVE_INCLUDE_DIRS	:=	$(addprefix ../../../, $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS	:=	$(addprefix ../../../$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS			:=	$(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS					:=	$(patsubst ../../../%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS					:=	$(OBJECTS:.cpp=.o)
OBJECTS					:=	$(OBJECTS:.c=.o)



$(PROGRAM_PATH):		obj_dirs $(OBJECTS)
						$(ARCHIVER) rc $@ $(OBJECTS)

obj_dirs:
						mkdir -p $(OBJECTS_DIRS)

VPATH					:= ../../../

%.o:					%.cpp
						$(COMPILER) $(COMPILE_FLAGS) $(BUILD_FLAGS) -c $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR)) -o $@ $<

.PHONY:					clean

all:
						mkdir -p $(BINARY_DIR)
						$(MAKE) --directory=./$(BINARY_DIR) --makefile=../../../Lib.mk

install:
						mkdir -p $(INSTALL_DIR)
						cp    ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)

						mkdir -p $(INSTALL_INCLUDE_DIR)
						cp -r ./$(ROOT_INCLUDE_DIR) $(INSTALL_INCLUDE_DIR)

clean:
						rm -rf $(BINARY_DIR)

include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))

