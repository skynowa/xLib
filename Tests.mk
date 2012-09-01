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
cOS 						:=  "$(shell uname -s)"

cBUILD_TYPE_DEBUG			:=	"debug"
cBUILD_TYPE_RELEASE			:=	"release"

cBIN_TYPE_LIB				:=	"static library"
cBIN_TYPE_TESTS				:=	"tests"

cCOMPILER					:=	$(CXX)
cARCHIVER					:=	$(AR)


##################################################
# xLib
ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	PROGRAM_PREFIX			:=
	PROGRAM_SHORT_NAME		:=	xlib
	PROGRAM_POSTFIX			:=	_d
	PROGRAM_EXT				:=
else
	PROGRAM_PREFIX			:=
	PROGRAM_SHORT_NAME		:=	xlib
	PROGRAM_POSTFIX			:=	_r
	PROGRAM_EXT				:=
endif

PATH_PREFIX					:=	../../../../
VPATH 						:=	$(PATH_PREFIX)

DIR_ROOT_INCLUDE			:=	./Project/Include
DIR_ROOT_SOURCE				:=	./Project/Source
DIR_TESTS_ROOT_INCLUDE		:=	./Tests/Include
DIR_TESTS_ROOT_SOURCE		:=	./Tests/Source

ifeq ($(cOS), "Linux")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN				:=	./Build/Tests/G++_linux/Debug
	else
		DIR_BIN				:=	./Build/Tests/G++_linux/Release
	endif
else
ifeq ($(cOS), "FreeBSD")
	ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
		DIR_BIN				:=	./Build/Tests/G++_freebsd/Debug
	else
		DIR_BIN				:=	./Build/Tests/G++_freebsd/Release
	endif
else
    $(error Unsupported OS: $(cOS))
endif
endif

PROGRAM_NAME				:=	$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_POSTFIX)$(PROGRAM_EXT)
PROGRAM_PATH				:=	../../../../$(DIR_BIN)/$(PROGRAM_NAME)

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
								Log \
								Net \
								Patterns \
								Sync \
								Sync/Win \
								Test \
								Units \
								Units/Win

DIR_OTHER_INCLUDE			:=	/usr/include \
								/usr/local/include

DIRS_LIB					:=	/usr/lib64 \
								/usr/lib \
								/usr/lib64/mysql \
								/usr/lib/mysql \
								/usr/local/lib64 \
								/usr/local/lib \
								/usr/local/lib64/mysql \
								/usr/local/lib/mysql

FLAGS_COMPILE				:=	$(CPPFLAGS) -Wall -pipe

ifeq ($(cOS), "Linux")
	LIBS					:=	$(LDFLAGS) -lrt -lmysqlclient -lm -lcrypto -lz -lssl -ldl
else
ifeq ($(cOS), "FreeBSD")
	LIBS					:=	$(LDFLAGS) -lrt -lmysqlclient -lm -lcrypto -lz -lssl -lexecinfo # -lc only with out -static
else
    $(error Unsupported OS: $(cOS))
endif
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	FLAGS_LINK				:=	-pthread -O0 -g3 -rdynamic #-static
else
	FLAGS_LINK				:=	-pthread -O3 -g0 -s -fomit-frame-pointer -rdynamic #-static
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
.PHONY:							all run clean help

all: 							$(PROGRAM_PATH)

run:
								$(DIR_BIN)/$(PROGRAM_NAME) 1 1 1 1

clean:
								if [ -d $(DIR_BIN) ]; then rm -rf $(DIR_BIN); fi

help:
								@echo -e ""
								@echo -e "+---------------------------------+"
								@echo -e "|   Tests.mk usage                |"
								@echo -e "+---------------------------------+"
								@echo -e "| all   - build tests             |"
								@echo -e "| run   - run tests               |"
								@echo -e "| clean - clean build             |"
								@echo -e "| help  - show help               |"
								@echo -e "----------------------------------+"
								@echo -e ""

include $(wildcard $(addsuffix /*.d, $(DIRS_OBJECTS)))
include $(wildcard $(addsuffix /*.d, $(TESTS_DIRS_OBJECTS)))

