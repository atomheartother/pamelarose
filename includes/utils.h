/*
** utils.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:26 2016 Thomas Navennec
** Last update Tue Oct 18 10:26:59 2016 Thomas Navennec
*/

#ifndef UTILS_H_
# define UTILS_H_

# define PATH_ROOT	"/home/"
# define FILE_PREFIX	"/."
# define FILE_NAME	"pamelaRose"

# define ERR_MALLOC	"Malloc failed"
# define ERR_PWD	"Could not obtain pwd data"
# define ERR_STAT	"stat failed on device"
# define ERR_EXECV	"Could not execute command"
# define ERR_CRYPT	"cryptsetup execution failed, removing file"
# define ERR_UNLINK	"Failed to delete file"

# define NAME_STR	"PR_"
# define PAM_USAGE	"pamelaRose [open|close|create|delete]"

char	*get_crypt_path(const char *name, const int flags);
char	*get_crypt_name(const char *uname, const int flags);
void	err_msg(const char * const msg, const int flags);
int	execute_file(char *exec, int argc, char *args[], int flags);
void	putstring(const char * const s);

#endif /* UTILS_H_ */
