/*
** mount_operations.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Wed Oct 19 10:36:18 2016 Thomas Navennec
** Last update Wed Oct 19 13:20:25 2016 Thomas Navennec
*/

#include <limits.h>
#include <string.h>
#include <sys/mount.h>
#include "utils.h"
#include "mount_operations.h"

int	pam_mount(const char *uname, const char *devicename,
		  const int flags)
{
  char	src[PATH_MAX] = {0};
  char	dest[PATH_MAX] = {0};

  strcat(src, MAPPER);
  strcat(src, devicename);
  strcat(dest, MOUNT_POINT);
  strcat(dest, uname);
  if (mount(src, dest, FSYSTEM, 0, NULL) == -1)
    {
      err_msg(ERR_MOUNT, flags);
      return 1;
    }
  return 0;
}

int		pam_umount(const char *uname, const char *devicename,
			   const int flags)
{
  char		target[PATH_MAX] = {0};

  strcat(target, MOUNT_POINT);
  strcat(target, uname);
  strcat(target, MOUNT_SEP);
  strcat(target, devicename);
  if (umount2(target, MNT_FORCE) == -1)
    {
      err_msg(ERR_UMOUNT, flags);
      return 1;
    }
  return 0;
}
