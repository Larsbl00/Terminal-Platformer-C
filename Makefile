#Project info
NAME = platformer

#Compiler info
CC = gcc
CFLAGS = -Wall -Werror

#Files
SOURCES = \

OBJECTS = $(SOURCES:.c=.o)

#Directories
SRC_DIR = ./src
OBJ_DIR = ./obj

#Targets
.PHONY: all clean 

all: create_directories

#Target to create necessary directories
create_directories:
	mkdir -p $(SRC_DIR)
	mkdir -p $(OBJ_DIR)



#Clean up
clean: 
	@#Remove all object files
	rm -rf $(OBJ_DIR)/$(wildcard *.o)

	@#Remove the executeable
	rm -f $(NAME)