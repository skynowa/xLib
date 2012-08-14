######################################################################################################
# File name:   Tests.mk
# Description: make file for tests (Unix OS)
#
######################################################################################################


##################################################
# settings
#BUILD_TYPE					:=	$(cBUILD_TYPE_DEBUG)
BUILD_TYPE					:=	$(cBUILD_TYPE_RELEASE)


##################################################
# constants
cOS                         :=  $(shell uname -s)

cBUILD_TYPE_DEBUG			:=	"debug"
cBUILD_TYPE_RELEASE			:=	"release"

cBIN_TYPE_LIB				:=	"static library"
cBIN_TYPE_TESTS				:=	"tests"

cCOMPILER					:=	$(CXX)
cARCHIVER					:=	$(AR)


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

DIR_ROOT_INCLUDE			:=	./Include
DIR_ROOT_SOURCE				:=	./Source
DIR_TESTS_ROOT_INCLUDE		:=	./Tests/Include
DIR_TESTS_ROOT_SOURCE		:=	./Tests/Source

ifeq ($(cOS), Linux)
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BINARY		:=	./Contrib/G++_linux/Debug
	else
		DIR_BINARY		:=	./Contrib/G++_linux/Release
	endif
else
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BINARY		:=	./Contrib/G++_freebsd/Debug
	else
		DIR_BINARY		:=	./Contrib/G++_freebsd/Release
	endif
endif

DIR_INSTALL					:=	/usr/local/lib/xLib

SUBDIRS_SOURCE				:=	. \
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

SUBDIRS_TESTS_SOURCE		:=	. \
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

DIR_OTHER_INCLUDE			:=	#/usr/include \
								#/usr/local/include

DIRS_LIB					:=	#/usr/lib64 \
								#/usr/lib \
								#/usr/lib64/mysql \
								#/usr/lib/mysql \
								#/usr/local/lib64 \
								#/usr/local/lib \
								#/usr/local/lib64/mysql \
								#/usr/local/lib/mysql

FLAGS_COMPILE				:=	$(CPPFLAGS) -Wall -pipe

ifeq ($(cOS), Linux)
LIBS						:=	$(LDFLAGS) -lmysqlclient -lm -lcrypto -lz -lssl -ldl
else
LIBS						:=	$(LDFLAGS) -lmysqlclient -lm -lcrypto -lz -lssl -lexecinfo # -lc only with out -static
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
FLAGS_LINK					:=	-pthread -O0 -g3 -rdynamic #-static
else
FLAGS_LINK					:=	-pthread -O3 -g0 -s -fomit-frame-pointer -rdynamic #-static
endif

DIRS_RELATIVE_INCLUDE		:=	$(addprefix $(PATH_PREFIX), $(DIR_ROOT_INCLUDE))
DIRS_RELATIVE_SOURCE		:=	$(addprefix $(PATH_PREFIX)$(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
DIRS_OBJECTS				:=	$(addprefix $(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
OBJECTS						:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.cpp, $(DIRS_RELATIVE_SOURCE))))
OBJECTS						:=	$(OBJECTS:.cpp=.o)

TESTS_DIRS_RELATIVE_INCLUDE	:=	$(addprefix $(PATH_PREFIX), $(DIR_TESTS_ROOT_INCLUDE))
TESTS_DIRS_RELATIVE_SOURCE	:=	$(addprefix $(PATH_PREFIX)$(DIR_TESTS_ROOT_SOURCE)/, $(SUBDIRS_TESTS_SOURCE))
TESTS_DIRS_OBJECTS			:=	$(addprefix $(DIR_TESTS_ROOT_SOURCE)/, $(SUBDIRS_TESTS_SOURCE))
TESTS_OBJECTS				:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.cpp, $(TESTS_DIRS_RELATIVE_SOURCE))))
TESTS_OBJECTS				:=	$(TESTS_OBJECTS:.cpp=.o)


$(PROGRAM_PATH): 				OBJ_DIRS $(OBJECTS) $(TESTS_OBJECTS) $(DIRS_RELATIVE_INCLUDE)
								$(cCOMPILER) $(OBJECTS) $(TESTS_OBJECTS) $(addprefix -L, $(DIRS_LIB)) $(FLAGS_LINK) $(LIBS) -o $@

OBJ_DIRS:
								mkdir -p $(DIRS_OBJECTS) $(TESTS_DIRS_OBJECTS)

%.o:							%.cpp
								$(cCOMPILER) -c $(FLAGS_COMPILE) $(FLAGS_LINK) $(addprefix -I, $(DIRS_RELATIVE_INCLUDE) $(TESTS_DIRS_RELATIVE_INCLUDE) $(DIR_OTHER_INCLUDE)) -o $@ $<


# targets
all: 							$(PROGRAM_PATH)


install:
								mkdir -p $(DIR_INSTALL)
								cp $(DIR_BINARY)/$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_EXT) $(DIR_INSTALL)

.PHONY:							clean
clean:
								rm -rf $(DIR_BINARY)

help:
								#TODO: help

include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))
include $(wildcard $(addsuffix /*.d, $(TESTS_DIRS_OBJECTS)))

