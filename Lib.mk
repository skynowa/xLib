######################################################################################################
# File name:   Lib.mk
# Description: make file for static library (Unix OS)
#
######################################################################################################


##################################################
# settings
#BUILD_TYPE				:=	$(cBUILD_TYPE_DEBUG)
BUILD_TYPE				:=	$(cBUILD_TYPE_RELEASE)


##################################################
# constants
cOS                     :=  "$(shell uname -s)"

cBUILD_TYPE_DEBUG		:=	"debug"
cBUILD_TYPE_RELEASE		:=	"release"

cBIN_TYPE_LIB			:=	"static library"
cBIN_TYPE_TESTS			:=	"tests"

cCOMPILER				:=	$(CXX)
cARCHIVER				:=	$(AR)


##################################################
# xLib
ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
    PROGRAM_PREFIX		:=	lib
    PROGRAM_SHORT_NAME	:=	xlib
    PROGRAM_POSTFIX		:=	_d
    PROGRAM_EXT			:=	.a
else
    PROGRAM_PREFIX		:=	lib
    PROGRAM_SHORT_NAME	:=	xlib
    PROGRAM_POSTFIX		:=	_r
    PROGRAM_EXT			:=	.a
endif

DIR_ROOT_INCLUDE		:=	./Project/Include
DIR_ROOT_SOURCE			:=	./Project/Source

DIR_OTHER_INCLUDE		:=	/usr/include \
							/usr/local/include

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

ifeq ($(cOS), "Linux")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BINARY		:=	./Build/Libs/G++_linux/Debug
	else
		DIR_BINARY		:=	./Build/Libs/G++_linux/Release
	endif
else
ifeq ($(cOS), "FreeBSD")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BINARY		:=	./Build/Libs/G++_freebsd/Debug
	else
		DIR_BINARY		:=	./Build/Libs/G++_freebsd/Release
	endif
else
    $(error Unsupported OS: $(cOS))
endif
endif

DIR_INSTALL_INCLUDE		:=	/usr/local/include
DIR_INSTALL				:=	/usr/local/lib
PROGRAM_NAME			:=	$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_POSTFIX)$(PROGRAM_EXT)
PROGRAM_PATH			:=	../../../../$(DIR_BINARY)/$(PROGRAM_NAME)

FLAGS_COMPILE			:=	$(CPPFLAGS) -Wall -pipe

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
    FLAGS_LINK			:=	-pthread -O0 -g3
else
    FLAGS_LINK			:=	-pthread -O3 -g0 -s -fomit-frame-pointer
endif

DIRS_RELATIVE_INCLUDE	:=	$(addprefix ../../../../, $(DIR_ROOT_INCLUDE))
DIRS_RELATIVE_SOURCE	:=	$(addprefix ../../../../$(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
DIRS_OBJECTS			:=	$(addprefix $(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
OBJECTS					:=	$(patsubst ../../../../%, %, $(wildcard $(addsuffix /*.cpp, $(DIRS_RELATIVE_SOURCE))))
OBJECTS					:=	$(OBJECTS:.cpp=.o)


$(PROGRAM_PATH):		OBJ_DIRS $(OBJECTS)
						$(cARCHIVER) -rc $@ $(OBJECTS)

OBJ_DIRS:
						mkdir -p $(DIRS_OBJECTS)

VPATH					:= ../../../../

%.o:					%.cpp
						$(cCOMPILER) -c $(FLAGS_COMPILE) $(FLAGS_LINK) $(addprefix -I, $(DIRS_RELATIVE_INCLUDE) $(DIR_OTHER_INCLUDE)) -o $@ $<


# targets
.PHONY:					all install uninstall clean help

all:
						mkdir -p $(DIR_BINARY)
						$(MAKE) --directory=$(DIR_BINARY) --makefile=../../../../Lib.mk

install:				uninstall

						mkdir -p $(DIR_INSTALL)
						cp    $(DIR_BINARY)/$(PROGRAM_NAME) $(DIR_INSTALL)/$(PROGRAM_NAME)

						mkdir -p $(DIR_INSTALL_INCLUDE)
						cp -r $(DIR_ROOT_INCLUDE)/xLib $(DIR_INSTALL_INCLUDE)

uninstall:
						if [ -f $(DIR_INSTALL)/$(PROGRAM_NAME) ]; then rm     $(DIR_INSTALL)/$(PROGRAM_NAME); fi
						if [ -d $(DIR_INSTALL_INCLUDE)/xLib    ]; then rm -rf $(DIR_INSTALL_INCLUDE)/xLib;    fi

clean:
						if [ -d $(DIR_BINARY) ]; then rm -rf $(DIR_BINARY); fi

help:
						@echo -e ""
						@echo -e "+---------------------------------------------+"
						@echo -e "|    Lib.mk usage                             |"
						@echo -e "+---------------------------------------------+"
						@echo -e "| all       - build static and share libs     |"
						@echo -e "| install   - install static and share libs   |"
						@echo -e "| uninstall - uninstall static and share libs |"
						@echo -e "| clean     - clean build                     |"
						@echo -e "| help      - show help                       |"
						@echo -e "+---------------------------------------------+"
						@echo -e ""


include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))

