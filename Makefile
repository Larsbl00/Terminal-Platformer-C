#Project info
NAME = platformer

#Compiler info
CC = gcc
CFLAGS = -Wall -Werror

#Files
SOURCES = \

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir ($(SOURCES))))

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



#Compile all objects from .c files
$(OBJ_DIR)/%.o: %.c:
	$(CC) -c $(CFLAGS) $^ -o $@

#Clean up
clean: 
	@#Remove all object files
	rm -rf $(OBJ_DIR)/$(wildcard *.o)

	@#Remove the executeable
	rm -f $(NAME)