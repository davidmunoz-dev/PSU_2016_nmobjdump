##
## Makefile for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump
## 
## Made by hazer
## Login   <david.munoz@epitech.eu>
## 
## Started on  Mon Feb 13 11:15:06 2017 hazer
## Last update Tue Feb 21 15:57:58 2017 hazer
##

TARGET	 = my_nm

CC	 = gcc

SRC      = error.c	\
	   utils.c	\
	   32bits.c	\
	   32bits_fc.c	\
	   64bits.c	\
	   64bits_fc.c	\
	   main.c

#CFLAGS   = -ldl -Iinclude

CFLAGS   = -W -Werror -Wall -ansi -ldl -Iinclude

SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(addprefix src/, $(SRC))

OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rm       = rm -rf
mkdir    = mkdir -p

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	@echo "\033[1;32m"$(TARGET)" compiled !\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(mkdir) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all     : $(TARGET)

clean   :
	@$(rm) $(OBJDIR)
	@echo "\033[1;31mBinary files deleted\033[0m"

fclean  : clean
	@$(rm) $(TARGET)
	@echo "\033[1;31mBinary and executable files are deleted\033[0m"

re      : fclean all

.PHONY: all clean fclean re
