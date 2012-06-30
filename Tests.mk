######################################################################################################
# File name:   Tests.mk
# Description: make file for tests (Unix OS)
#
######################################################################################################


##################################################
# Constants
cOS                         :=  $(shell uname -s)

cBUILD_TYPE_DEBUG			:=	debug
cBUILD_TYPE_RELEASE			:=	release

cBIN_TYPE_LIB				:=	static library
cBIN_TYPE_TESTS				:=	tests

cDESCRIPTION 				:=	tests for xLib

cCOMPILER					:=	$(CXX)
cARCHIVER					:=	$(AR)


##################################################
# Settings
#BUILD_TYPE					:=	$(cBUILD_TYPE_DEBUG)
BUILD_TYPE					:=	$(cBUILD_TYPE_RELEASE)


##################################################
# xLib
ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
PROGRAM_PREFIX				:=
PROGRAM_SHORT_NAME			:=	xlib
PROGRAM_POSTFIX				:=	_d
PROGRAM_EXT					:=
else
PROGRAM_PREFIX				:=
PROGRAM_SHORT_NAME			:=	xlib
PROGRAM_POSTFIX				:=	_r
PROGRAM_EXT					:=
endif

PROGRAM_NAME				:=	$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_POSTFIX)$(PROGRAM_EXT)
PROGRAM_PATH				:=	$(PROGRAM_NAME)

PATH_PREFIX					:=	../../../
VPATH 						:=	$(PATH_PREFIX)

ROOT_INCLUDE_DIR			:=	./Include
ROOT_SOURCE_DIR				:=	./Source
TESTS_ROOT_INCLUDE_DIR		:=	./Tests/Include
TESTS_ROOT_SOURCE_DIR		:=	./Tests/Source

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BINARY_DIR					:=	./Contrib/G++_linux/Debug
else
BINARY_DIR					:=	./Contrib/G++_linux/Release
endif

INSTALL_DIR					:=	/usr/local/lib/xLib

SOURCE_SUBDIRS				:=	. \
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
								Test \
								Units \
								Units/Win

TESTS_SOURCE_SUBDIRS		:=	. \
								Common \
								Common/Win \
								Crypt \
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

OTHER_INCLUDE_DIR			:=	/usr/include \
								/usr/local/include

LIB_DIRS					:=	/usr/lib64 \
								/usr/lib \
								/usr/lib64/mysql \
								/usr/lib/mysql \
								/usr/local/lib64 \
								/usr/local/lib \
								/usr/local/lib64/mysql \
								/usr/local/lib/mysql

COMPILE_FLAGS				:=	$(CPPFLAGS) -Wall -pipe

ifeq ($(cOS), Linux)
LIBS						:=	$(LDFLAGS) -lmysqlclient -lm -lcrypto -lz -lssl -ldl
else
LIBS						:=	$(LDFLAGS) -lmysqlclient -lm -lcrypto -lz -lssl -lexecinfo # -lc only with out -static
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
LINK_FLAGS					:=	-pthread -s -pipe -O0 -g3 -g -fexceptions -rdynamic	#-static
else
LINK_FLAGS					:=	-pthread -s -pipe -O3 -g0 -fomit-frame-pointer -fexceptions -rdynamic	#-static
endif

PARANOID_FLAGS				:=	-pedantic -Wall -Wextra -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default \
								-Wswitch-enum -Wsync-nand -Wstrict-overflow=1 -Wstrict-overflow=2 -Wstrict-overflow=3 \
								-Wstrict-overflow=4 -Wstrict-overflow=5 -Wfloat-equal -Wtraditional -Wtraditional-conversion \
								-Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wtype-limits \
								-Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
								-Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-declaration \
								-Wold-style-definition -Wmissing-prototypes  -Wmissing-declarations \
								-Wmissing-field-initializers -Wmissing-format-attribute -Wpacked -Wpadded \
								-Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wvariadic-macros -Wvla \
								-Wvolatile-register-var -Wdisabled-optimization -Wpointer-sign -Wstack-protector

RELATIVE_INCLUDE_DIRS		:=	$(addprefix $(PATH_PREFIX), $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS		:=	$(addprefix $(PATH_PREFIX)$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS				:=	$(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS						:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.cpp, $(RELATIVE_SOURCE_DIRS))))
OBJECTS						:=	$(OBJECTS:.cpp=.o)

TESTS_RELATIVE_INCLUDE_DIRS	:=	$(addprefix $(PATH_PREFIX), $(TESTS_ROOT_INCLUDE_DIR))
TESTS_RELATIVE_SOURCE_DIRS	:=	$(addprefix $(PATH_PREFIX)$(TESTS_ROOT_SOURCE_DIR)/, $(TESTS_SOURCE_SUBDIRS))
TESTS_OBJECTS_DIRS			:=	$(addprefix $(TESTS_ROOT_SOURCE_DIR)/, $(TESTS_SOURCE_SUBDIRS))
TESTS_OBJECTS				:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.cpp, $(TESTS_RELATIVE_SOURCE_DIRS))))
TESTS_OBJECTS				:=	$(TESTS_OBJECTS:.cpp=.o)


$(PROGRAM_PATH): 				OBJ_DIRS $(OBJECTS) $(TESTS_OBJECTS) $(RELATIVE_INCLUDE_DIRS)
								$(cCOMPILER) $(OBJECTS) $(TESTS_OBJECTS) $(addprefix -L, $(LIB_DIRS)) $(LINK_FLAGS) $(LIBS) -o $@

OBJ_DIRS:
								mkdir -p $(OBJECTS_DIRS) $(TESTS_OBJECTS_DIRS)

%.o:							%.cpp
								$(cCOMPILER) -c $(COMPILE_FLAGS) $(LINK_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(TESTS_RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR)) -o $@ $<


# targets
all: 							$(PROGRAM_PATH)


install:
								mkdir -p $(INSTALL_DIR)
								cp $(BINARY_DIR)/$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_EXT) $(INSTALL_DIR)

.PHONY:							clean
clean:
								rm -rf $(BINARY_DIR)

help:
								#TODO: help

include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))
include $(wildcard $(addsuffix /*.d, $(TESTS_OBJECTS_DIRS)))

