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
# define MOUNT_DIR	"/pamelaRose"
# define MSG_MKFS	"Creating ext4 filesystem..."
# define ERR_MOUNT	"Mount failed"
# define ERR_UMOUNT	"Unmount failed"
# define ERR_MKDIR	"mkdir failed"
# define ERR_UMKDIR	"Can't delete object to make room for pamelaRose directory"
# define ERR_PWD	"Could not retrieve username information"
# define ERR_CHOWN	"Could not grant rights to user"

# define MKFS_PATH	"/sbin/mkfs.ext4"
# define MKFS_ARG0	"mkfs.ext4"
# define MKFS_ARG1	"-j"

int	pam_mount(const char *uname,
		  const char *devicename,
		  const int flags);
int	pam_umount(const char *uname,
		   const char *devicename,
		   const int flags);
int	pam_mkfs(const char *name,
		 const int flags);

#endif
