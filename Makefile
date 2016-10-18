##
## Makefile for  in /home/navenn_t/Programmation/crypto/Pamela
## 
## Made by Thomas Navennec
## Login   <navenn_t@epitech.net>
## 
## Started on  Sun Oct  9 18:28:59 2016 Thomas Navennec
## Last update Tue Oct 18 11:12:35 2016 Thomas Navennec
##

ARCH := $(shell getconf LONG_BIT)

NAME = pam_elarose.so
NAMEBIN = pamelaRose

CC = gcc

CFLAGS_32 += -m32
CFLAGS_64 += -m64

CFLAGS += $(CFLAGS_$(ARCH))
CFLAGS += -I./includes/
CFLAGS += -Wall -Wextra

LIBS += -lcryptsetup -lpam

SRCDIR = ./src/
OBJDIR = ./obj/
DESTDIR = /lib/x86_64-linux-gnu/security/

SRC =	$(SRCDIR)pam_elarose.c		\
	$(SRCDIR)utils.c		\
	$(SRCDIR)new_path_container.c	\
	$(SRCDIR)get_next_line.c	\
	$(SRCDIR)cryptsetup.c		\
	$(SRCDIR)open_container.c	\
	$(SRCDIR)pam.c			\
	$(SRCDIR)close_container.c

SRCBIN = $(SRCDIR)main.c

OBJ	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)shared_%.o,$(SRC))

OBJBIN	= $(patsubst $(SRCDIR)%.c,$(OBJDIR)bin_%.o,$(SRCBIN) $(SRC))

RM = rm -rf

all: $(NAME) $(NAMEBIN)

# Do not do this outside the VM!
# Installs the binary in the right directory FOR DEBIAN ONLY!
install: all
	@test -d $(DESTDIR) || mkdir -p $(DESTDIR) && cp $(NAME) $(DESTDIR)

$(NAME): $(OBJ)
	$(CC) -shared $(LIBS) -o $@ $(OBJ) $(CFLAGS)

$(NAMEBIN): $(OBJBIN)
	$(CC) $(LIBS) -o $@ $(OBJBIN) $(CFLAGS)

$(OBJ): | $(OBJDIR)
$(OBJBIN): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)shared_%.o : $(SRCDIR)%.c
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

$(OBJDIR)bin_%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMEBIN)

re: fclean all
