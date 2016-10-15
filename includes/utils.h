/*
** utils.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:26 2016 Thomas Navennec
** Last update Fri Oct 14 17:07:59 2016 Thomas Navennec
*/

#ifndef UTILS_H_
# define UTILS_H_

#include <security/pam_modules.h>

# define PATH_ROOT	"/home/"
# define FILE_PREFIX	"/"
# define FILE_NAME	"pamelaRose"

# define ERR_MALLOC	"Malloc failed"
# define ERR_UNAME	"Could not get username"
# define ERR_STAT	"stat failed on device"
# define ERR_EXECV	"Could not execute command"

char	*get_crypt_path(pam_handle_t *pamh, const int flags);
void	err_msg(const char * const msg, const int flags);

#endif /* UTILS_H_ */
