##
## Makefile for  in /home/navenn_t/Programmation/crypto/Pamela
## 
## Made by Thomas Navennec
## Login   <navenn_t@epitech.net>
## 
## Started on  Sun Oct  9 18:28:59 2016 Thomas Navennec
## Last update Sat Oct 15 03:31:29 2016 Thomas Navennec
##

ARCH := $(shell getconf LONG_BIT)

NAME = pam_elarose.so

CC = gcc

CFLAGS_32 += -m32
CFLAGS_64 += -m64

CFLAGS += $(CFLAGS_$(ARCH))
CFLAGS += -fPIC -I./includes/
CFLAGS += -Wall -Wextra

SRCDIR = ./src/
OBJDIR = ./obj/
DESTDIR = /lib/x86_64-linux-gnu/security/

SRC =	$(SRCDIR)pam_elarose.c		\
	$(SRCDIR)utils.c		\
	$(SRCDIR)new_path_container.c	\
	$(SRCDIR)get_next_line.c

OBJ	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

RM = rm -rf

all: $(NAME)

# Do not do this outside the VM!
install: all
	@test -d $(DESTDIR) || mkdir -p $(DESTDIR) && cp $(NAME) $(DESTDIR)

$(NAME): $(OBJ)
	$(CC) -shared -o $@ $(OBJ) -lpam $(CFLAGS_$(ARCH))

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
