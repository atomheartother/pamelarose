##
## Makefile for  in /home/navenn_t/Programmation/crypto/Pamela
## 
## Made by Thomas Navennec
## Login   <navenn_t@epitech.net>
## 
## Started on  Sun Oct  9 18:28:59 2016 Thomas Navennec
## Last update Sun Oct  9 19:27:22 2016 Thomas Navennec
##

NAME = pam_elarose.so
NAME64 = pam_elarose64.so
NAME32 = pam_elarose32.so

CC = gcc

CFLAGS += -fPIC -I./includes/

SRCDIR = ./src/
OBJDIR = ./obj/

SRC = $(SRCDIR)pam_elarose.c

OBJ64	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)64%.o,$(SRC))
OBJ32	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)32%.o,$(SRC))

RM = rm -rf

all: $(NAME64) $(NAME32)

install: $(NAME64) $(NAME32)
	cp $(NAME64) /usr/lib64/security/$(NAME)
	cp $(NAME32) /usr/lib/security/$(NAME)

$(NAME64): $(OBJ64)
	$(CC) -shared -o $@ $(OBJ) -lpam

$(NAME32): $(OBJ32)
	$(CC) -shared -o $@ $(OBJ) -lpam

$(OBJ32): | $(OBJDIR)
$(OBJ64): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)%64.o : $(SRCDIR)%.c
	$(CC) -m64 $(CFLAGS) -c $< -o $@

$(OBJDIR)%32.o : $(SRCDIR)%.c
	$(CC) -m32 $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME64) $(NAME32)

re: fclean all
