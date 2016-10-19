/*
** mount_operations.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Wed Oct 19 10:27:52 2016 Thomas Navennec
** Last update Wed Oct 19 12:10:31 2016 Thomas Navennec
*/

#ifndef MOUNT_OPERATIONS_H_
# define MOUNT_OPERATIONS_H_

# define MOUNT_POINT	"/home/"
# define MAPPER		"/dev/mapper/"
# define FSYSTEM	"ext4"
# define MOUNT_SEP	"/"

# define ERR_MOUNT	"Mount failed"
# define ERR_UMOUNT	"Unmount failed"

int	pam_mount(const char *uname,
		  const char *devicename,
		  const int flags);
int	pam_umount(const char *uname,
		   const char *devicename,
		   const int flags);

#endif
