/*
** utils.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:26 2016 Thomas Navennec
** Last update Wed Oct 19 10:58:47 2016 Thomas Navennec
*/

#ifndef UTILS_H_
# define UTILS_H_

# define PATH_ROOT	"/home/"
# define FILE_PREFIX	"/."
# define FILE_NAME	"pamelaRose"

# define ERR_MALLOC	"Malloc failed"
# define ERR_STAT	"stat failed on device"
# define ERR_EXECV	"Could not execute command"
# define ERR_CRYPT	"cryptsetup execution failed, removing file"
# define ERR_UNLINK	"Failed to delete file"

# define NAME_STR	"PR_"
# define PAM_USAGE	"pamelaRose (username) (open|close|create|delete)"
# define ROOTREQ	"You need to be root to manage containers"
# define PAM_BADUNAME	"This username is invalid"
# define PAM_DELETED	"Container deleted"

# define MKFS_FLAG      0x4000U
# define UMOUNT_FLAG	0x2000U
# define ERRNO_FLAG	0x1000U

char	*get_crypt_path(const char *name, const int flags);
char	*get_crypt_name(const char *uname, const int flags);
void	err_msg(const char * const msg, const int flags);
int	execute_file(char *exec, int argc, char *args[], const int flags);
void	putstring(const char * const s);
char	*concat_and_alloc(const char *s1, const char *s2);

#endif /* UTILS_H_ */
