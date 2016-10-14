/*
** new_pam_container.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 17:03:26 2016 Thomas Navennec
** Last update Fri Oct 14 18:15:07 2016 Thomas Navennec
*/

#ifndef NEW_PAM_CONTAINER
# define NEW_PAM_CONTAINER

# include <security/pam_modules.h>

# define NEWPAM_WELCOME	"Welcome to the PAMelaRose container creation."
# define NEWPAM_PROMPT	"Would you like to create an encrypted container? [Y/n]:"
# define NEWPAM_SIZE	"Please enter the desired size for your container (in MB):"
# define NEWPAM_ERR	"Invalid input, expected digits."
# define NEWPAM_DONE	"Container created:"

/*
** Making this <= 0 will break things.
*/
# define NEWPAM_MAX_TRIES	30

int	new_pam_container(pam_handle_t *pamh,
			  const char * const path,
			  int flags);

#endif /* NEW_PAM_CONTAINER */
