#Project info
NAME = platformer

#Compiler info
CC = gcc
CFLAGS = -Wall -Werror

#Files
SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/KeyReader.c \
	$(SRC_DIR)/RenderQueueItem.c \
	$(SRC_DIR)/RenderQueue.c \
	$(SRC_DIR)/RenderWindow.c \
	$(SRC_DIR)/Rectangle.c \
	$(SRC_DIR)/Player.c \
	$(SRC_DIR)/Level.c

#Create .o files in the obj folder for every file
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))

#Create a vpath to all directories in the sources
VPATH = $(sort $(dir $(SOURCES)))

#Directories
SRC_DIR = ./src
OBJ_DIR = ./obj

#Targets
.PHONY: all clean 

#Default target
all: create_directories $(NAME)

#Target to create necessary directories
create_directories:
	mkdir -p $(SRC_DIR)
	mkdir -p $(OBJ_DIR)

#Compile the executable
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

#Compile all objects from .c files
$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

#Clean up
clean: 
	@#Remove all object files
	rm -rf $(OBJ_DIR)/$(wildcard *.o)

	@#Remove the executeable
	rm -f $(NAME)