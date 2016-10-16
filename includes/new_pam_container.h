/*
** new_pam_container.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 17:03:26 2016 Thomas Navennec
** Last update Sun Oct 16 15:38:44 2016 Thomas Navennec
*/

#ifndef NEW_PAM_CONTAINER
# define NEW_PAM_CONTAINER

# include <security/pam_modules.h>

# define NEWPAM_WELCOME	"Welcome to the PAMelaRose container creation.\n"
# define NEWPAM_PROMPT	"Would you like to create an encrypted container? [Y/n]:"
# define NEWPAM_SIZE	"Please enter the desired size for your container (in MB):"
# define NEWPAM_ERR	"Invalid input, expected digits."
# define NEWPAM_DONE	"Container created:"

# define DD_EXE		"/bin/dd"
# define DD_ARG0	"dd"
# define DD_ARG1	"if=/dev/urandom"
# define DD_ARG2	"of="
# define DD_ARG3	"bs=1M"
# define DD_ARG4	"count="

# define CR_EXE		"/bin/cryptsetup"
# define CR_ARG0	"cryptsetup"
# define CR_ARG1	"-y"
# define CR_ARG2	"luksFormat"

/*
** Tries the user gets to enter the size of his container
*/
# define NEWPAM_MAX_TRIES	20

int	new_pam_container(pam_handle_t *pamh,
			  char * path,
			  int flags);

#endif /* NEW_PAM_CONTAINER */
