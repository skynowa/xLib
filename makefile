######################################################################################################
# Class name:  
# Description: make file (Linux, release)
# File name:   makefile
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


PROGRAM_NAME            := xLib.a

ROOT_INCLUDE_DIR   	:= Include Source
ROOT_SOURCE_DIR    	:= Source
SOURCE_SUBDIRS     	:= 	.\
				Units \
				Sync \
				Patterns \
				Net \
				Log \
				Filesystem \
				Debug \
				Db \
				Crypt/OpenSSL \
				Crypt \
				Compress/Linux \
				Common
BINARY_DIR              := Library/G++_linux/Release
INSTALL_DIR		:= .
PROGRAM_PATH            := ../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER                := g++
COMPILE_FLAGS      	:= -Wall -MD -pipe
BUILD_FLAGS             := -O3 -fomit-frame-pointer -pthread -g0 -s #-g

RELATIVE_INCLUDE_DIRS	:= $(addprefix ../../../, $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS   	:= $(addprefix ../../../$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS            := $(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS                 := $(patsubst ../../../%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS                 := $(OBJECTS:.cpp=.o)
OBJECTS                 := $(OBJECTS:.c=.o)



$(PROGRAM_PATH):	obj_dirs $(OBJECTS)
			ar rcs $@ $(OBJECTS)

obj_dirs:	        
			mkdir -p $(OBJECTS_DIRS)

VPATH			:= ../../../

%.o: 			%.cpp
			$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS))

%.o: 			%.c
			$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS))

.PHONY:			clean


all:		
# 			@echo "\n******************* prepare ********************"
			mkdir -p $(BINARY_DIR)

# 			@echo "\n******************** compile ********************"
			$(MAKE) --directory=./$(BINARY_DIR) --makefile=../../../makefile

install:
# 			@echo "\n******************** install ********************"
			cp ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)/$(PROGRAM_NAME)

clean:
# 			@echo "\n******************** clean ********************"
			rm -rf $(BINARY_DIR)


include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))
