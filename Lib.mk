################################################################################
# File name:   Lib.mk
# Description: make file for static library (Unix OS)
#
################################################################################


################################################################################
# constants
cOS 				:=	"$(shell uname -s | tr "a-z" "A-Z" | cut -b 1-7)"

cBUILD_TYPE_DEBUG	:=	"debug"
cBUILD_TYPE_RELEASE	:=	"release"

cBIN_TYPE_LIB		:=	"static library"
cBIN_TYPE_TESTS		:=	"tests"

cCOMPILER			:=	$(CXX)
cARCHIVER			:=	$(AR)

################################################################################
# settings
BUILD_TYPE			:=	$(cBUILD_TYPE_DEBUG)
#BUILD_TYPE			:=	$(cBUILD_TYPE_RELEASE)

################################################################################
# xLib
ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	APP_PREFIX		:=	lib
	APP_SHORT_NAME	:=	xlib
	APP_POSTFIX		:=	_d
	APP_EXT			:=	.a
else
	APP_PREFIX		:=	lib
	APP_SHORT_NAME	:=	xlib
	APP_POSTFIX		:=	_r
	APP_EXT			:=	.a
endif

DIR_ROOT_INCLUDE	:=	./Project/Include
DIR_ROOT_SOURCE		:=	./Project/Source

DIR_OTHER_INCLUDE	:=	/usr/include \
						/usr/local/include

SUBDIRS_SOURCE		:=	. \
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
						Log \
						Net \
						Patterns \
						Sync \
						Sync/Win \
						Test

DIRS_LIB			:=	/usr/lib64 \
						/usr/lib \
						/usr/lib64/mysql \
						/usr/lib/mysql \
						/usr/local/lib64 \
						/usr/local/lib \
						/usr/local/lib64/mysql \
						/usr/local/lib/mysql

ifeq ($(cOS), "MINGW32")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Libs/MinGW/Debug
	else
		DIR_BIN		:=	./Build/Libs/MinGW/Release
	endif
else
ifeq ($(cOS), "LINUX")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Libs/GCC_linux/Debug
	else
		DIR_BIN		:=	./Build/Libs/GCC_linux/Release
	endif
else
ifeq ($(cOS), "FREEBSD")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Libs/GCC_freebsd/Debug
	else
		DIR_BIN		:=	./Build/Libs/GCC_freebsd/Release
	endif
else
    $(error Unsupported OS: $(cOS))
endif
endif
endif

DIR_INSTALL_INCLUDE	:=	/usr/local/include
DIR_INSTALL			:=	/usr/local/lib
APP_NAME			:=	$(APP_PREFIX)$(APP_SHORT_NAME)$(APP_POSTFIX)$(APP_EXT)
APP_PATH			:=	../../../../$(DIR_BIN)/$(APP_NAME)

DEFINES				:=	-D_LIB	# In Unix this defines (_LIB, _DLL) must be set from Makefile
FLAGS_COMPILE		:=	$(CPPFLAGS) -Wall -pipe $(DEFINES)

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	FLAGS_LINK		:=	-pthread -O0 -g3
else
	FLAGS_LINK		:=	-pthread -O3 -g0 -s -fomit-frame-pointer
endif

DIRS_REL_INCLUDE	:=	$(addprefix ../../../../, $(DIR_ROOT_INCLUDE))
DIRS_REL_SOURCE		:=	$(addprefix ../../../../$(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
DIRS_OBJECTS		:=	$(addprefix $(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
OBJECTS				:=	$(patsubst ../../../../%, %, $(wildcard $(addsuffix /*.cpp, $(DIRS_REL_SOURCE))))
OBJECTS				:=	$(OBJECTS:.cpp=.o)


$(APP_PATH):		OBJ_DIRS $(OBJECTS)
					$(cARCHIVER) -rc $@ $(OBJECTS)

OBJ_DIRS:
					mkdir -p $(DIRS_OBJECTS)

VPATH				:= ../../../../

%.o:				%.cpp
					$(cCOMPILER) -c $(FLAGS_COMPILE) $(FLAGS_LINK) \
					$(addprefix -I, $(DIRS_REL_INCLUDE) $(DIR_OTHER_INCLUDE)) \
					-o $@ $<

################################################################################
# targets
.PHONY:				all install uninstall clean help

all:
					mkdir -p $(DIR_BIN)
					$(MAKE) --directory=$(DIR_BIN) --makefile=../../../../Lib.mk

install:			uninstall

					mkdir -p $(DIR_INSTALL)
					cp $(DIR_BIN)/$(APP_NAME) $(DIR_INSTALL)/$(APP_NAME)

					mkdir -p $(DIR_INSTALL_INCLUDE)
					cp -r $(DIR_ROOT_INCLUDE)/xLib $(DIR_INSTALL_INCLUDE)

uninstall:
					if [ -f $(DIR_INSTALL)/$(APP_NAME)  ]; then rm     $(DIR_INSTALL)/$(APP_NAME);  fi
					if [ -d $(DIR_INSTALL_INCLUDE)/xLib ]; then rm -rf $(DIR_INSTALL_INCLUDE)/xLib; fi

clean:
					if [ -d $(DIR_BIN) ]; then rm -rf $(DIR_BIN); fi

help:
					@echo -e ""
					@echo -e "+-------------------------------------------+"
					@echo -e "|    Lib.mk usage                           |"
					@echo -e "+-------------------------------------------+"
					@echo -e "| all       - build static, share libs      |"
					@echo -e "| install   - install static, share libs    |"
					@echo -e "| uninstall - uninstall static, share libs  |"
					@echo -e "| clean     - clean build                   |"
					@echo -e "| help      - show help                     |"
					@echo -e "+-------------------------------------------+"
					@echo -e ""


include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))
