##
## Makefile for  in /home/navenn_t/Programmation/crypto/Pamela
## 
## Made by Thomas Navennec
## Login   <navenn_t@epitech.net>
## 
## Started on  Sun Oct  9 18:28:59 2016 Thomas Navennec
## Last update Sun Oct  9 18:38:25 2016 Thomas Navennec
##

NAME = pam_elarose.so

CC = gcc

CFLAGS += -fPIC

SRCDIR = ./src/
OBJDIR = ./obj/

SRC = $(SRCDIR)pam_elarose.c

OBJ	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) -lpam

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
