################################################################################
# File name:   Tests.mk
# Description: make file for tests (Unix OS)
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
	APP_PREFIX		:=
	APP_SHORT_NAME	:=	xlib
	APP_POSTFIX		:=	_d
	APP_EXT			:=
else
	APP_PREFIX		:=
	APP_SHORT_NAME	:=	xlib
	APP_POSTFIX		:=	_r
	APP_EXT			:=
endif

DIR_ROOT_INCLUDE		:=	./Project/Include
DIR_ROOT_SOURCE			:=	./Project/Source
DIR_TESTS_ROOT_INCLUDE	:=	./Tests/Include
DIR_TESTS_ROOT_SOURCE	:=	./Tests/Source

ifeq ($(cOS), "MINGW32")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Tests/MinGW/Debug
	else
		DIR_BIN		:=	./Build/Tests/MinGW/Release
	endif
else
ifeq ($(cOS), "Linux")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Tests/GCC_linux/Debug
	else
		DIR_BIN		:=	./Build/Tests/GCC_linux/Release
	endif
else
ifeq ($(cOS), "FreeBSD")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN		:=	./Build/Tests/GCC_freebsd/Debug
	else
		DIR_BIN		:=	./Build/Tests/GCC_freebsd/Release
	endif
else
    $(error Unsupported OS: $(cOS))
endif
endif
endif

APP_NAME			:=	$(APP_PREFIX)$(APP_SHORT_NAME)$(APP_POSTFIX)$(APP_EXT)
APP_PATH			:=	../../../../$(DIR_BIN)/$(APP_NAME)

SUBDIRS_SOURCE		:=	. \
						Common \
						Common/Win \
						Crypt \
						#Crypt/OpenSSL \
						#Crypt/Pkcs11/Win \
						Db \
						Debug \
						Filesystem \
						Filesystem/Win \
						Gui \
						Gui/Dialogs \
						Log \
						Net \
						Patterns \
						Sync \
						Sync/Win \
						Sync/Unix \
						Test

SUBDIRS_TESTS_SOURCE:=	. \
						Common \
						Common/Win \
						#Crypt \
						#Crypt/Pkcs11 \
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
						Test

DIR_OTHER_INCLUDE	:=	/usr/include \
						/usr/local/include

DIRS_LIB			:=	/usr/lib64 \
						/usr/lib \
						/usr/lib64/mysql \
						/usr/lib/mysql \
						/usr/local/lib64 \
						/usr/local/lib \
						/usr/local/lib64/mysql \
						/usr/local/lib/mysql

DEFINES				:=	
FLAGS_COMPILE		:=	$(CPPFLAGS) -Wall -pipe $(DEFINES)

ifeq ($(cOS), "MINGW32")
	LIBS			:=	$(LDFLAGS) -lws2_32 -lpsapi -luuid -lole32 -lmpr
else
ifeq ($(cOS), "Linux")
	LIBS			:=	$(LDFLAGS) -lpthread -lrt -lmysqlclient -lm -lcrypto -lz -lssl -ldl
else
ifeq ($(cOS), "FreeBSD")
	LIBS			:=	$(LDFLAGS) -lpthread -lrt -lmysqlclient -lm -lcrypto -lz -lssl -lexecinfo # -lc only with out -static
else
    $(error Unsupported OS: $(cOS))
endif
endif
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	FLAGS_LINK		:=	-O0 -g3 -rdynamic #-static
else
	FLAGS_LINK		:=	-O3 -g0 -s -fomit-frame-pointer -rdynamic #-static
endif

DIRS_REL_INCLUDE	:=	$(addprefix ../../../../, $(DIR_ROOT_INCLUDE))
DIRS_REL_SOURCE		:=	$(addprefix ../../../../$(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
DIRS_OBJECTS		:=	$(addprefix $(DIR_ROOT_SOURCE)/, $(SUBDIRS_SOURCE))
OBJECTS				:=	$(patsubst ../../../../%, %, $(wildcard $(addsuffix /*.cpp, $(DIRS_REL_SOURCE))))
OBJECTS				:=	$(OBJECTS:.cpp=.o)

TESTS_DIRS_REL_INCLUDE	:=	$(addprefix ../../../../, $(DIR_TESTS_ROOT_INCLUDE))
TESTS_DIRS_REL_SOURCE	:=	$(addprefix ../../../../$(DIR_TESTS_ROOT_SOURCE)/, $(SUBDIRS_TESTS_SOURCE))
TESTS_DIRS_OBJECTS	:=	$(addprefix $(DIR_TESTS_ROOT_SOURCE)/, $(SUBDIRS_TESTS_SOURCE))
TESTS_OBJECTS		:=	$(patsubst ../../../../%, %, $(wildcard $(addsuffix /*.cpp, $(TESTS_DIRS_REL_SOURCE))))
TESTS_OBJECTS		:=	$(TESTS_OBJECTS:.cpp=.o)


$(APP_PATH): 		OBJ_DIRS $(OBJECTS) $(TESTS_OBJECTS) $(DIRS_REL_INCLUDE)
					$(cCOMPILER) $(OBJECTS) $(TESTS_OBJECTS) \
					$(addprefix -L, $(DIRS_LIB)) $(FLAGS_LINK) $(LIBS) \
					-o $@

OBJ_DIRS:
					mkdir -p $(DIRS_OBJECTS) $(TESTS_DIRS_OBJECTS)

VPATH 				:=	../../../../

%.o:				%.cpp
					$(cCOMPILER) -c $(FLAGS_COMPILE) $(FLAGS_LINK) \
					$(addprefix -I, $(DIRS_REL_INCLUDE) $(TESTS_DIRS_REL_INCLUDE) $(DIR_OTHER_INCLUDE)) \
					-o $@ $<

################################################################################
# targets
.PHONY:				all run clean help

all:
					mkdir -p $(DIR_BIN)
					$(MAKE) --directory=$(DIR_BIN) --makefile=../../../../Tests.mk

run:
					$(DIR_BIN)/$(APP_NAME) 1 1 1 1

clean:
					if [ -d $(DIR_BIN) ]; then rm -rf $(DIR_BIN); fi

help:
					@echo -e ""
					@echo -e "+-------------------------------------------+"
					@echo -e "|   Tests.mk usage                          |"
					@echo -e "+-------------------------------------------+"
					@echo -e "| all   - build tests                       |"
					@echo -e "| run   - run tests                         |"
					@echo -e "| clean - clean build                       |"
					@echo -e "| help  - show help                         |"
					@echo -e "+-------------------------------------------+"
					@echo -e ""

include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))
include $(wildcard $(addsuffix /*.d, $(TESTS_DIRS_OBJECTS)))
