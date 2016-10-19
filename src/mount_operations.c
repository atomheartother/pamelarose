/*
** mount_operations.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Wed Oct 19 10:36:18 2016 Thomas Navennec
** Last update Wed Oct 19 13:20:25 2016 Thomas Navennec
*/

#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mount.h>
#include <stdlib.h>
#include "utils.h"
#include "mount_operations.h"

int	create_dir(const char *dest,
		   const int flags)
{
  struct stat	st;

  if (stat(dest, &st) == -1)
    {
      if (errno != ENOENT)
	{
	  err_msg(ERR_STAT, flags + ERRNO_FLAG);
	  return 1;
	}
    }
  else
    {
      if (st.st_mode & S_IFDIR)
	return 0;
      else if (unlink(dest) == -1)
	{
	  err_msg(ERR_UMKDIR, flags + ERRNO_FLAG);
	  return 1;
	}
    }
  printf("Creating directory: %s\n", dest);
  if (mkdir(dest, 0644) == -1)
    {
      err_msg(ERR_MKDIR, flags + ERRNO_FLAG);
      return 1;
    }
  return 0;
}

int	pam_mount(const char *uname, const char *devicename,
		  const int flags)
{
  char	src[PATH_MAX] = {0};
  char	dest[PATH_MAX] = {0};

  strcat(src, MAPPER);
  strcat(src, devicename);
  strcat(dest, MOUNT_POINT);
  strcat(dest, uname);
  strcat(dest, "/pamelaRose");
  
  if (create_dir(dest, flags))
    return 1;
  if (mount(src, dest, FSYSTEM, 0, NULL) == -1)
    {
      err_msg(ERR_MOUNT, flags + ERRNO_FLAG);
      return 1;
    }
  /*
  ** We get user info and give him rights over the folder
  */
  struct passwd *pwd = getpwnam(uname);
  int		err = 0;
  if (!pwd)
    {
      err_msg(ERR_PWD, flags);
      err = 1;
    }
  if (!err && chown(dest, pwd->pw_uid, pwd->pw_gid) == -1)
    {
      err_msg(ERR_CHOWN, flags);
      err = 1;
    }
  if (err)
    pam_umount(uname, devicename, flags);
  return err;
}

int		pam_umount(const char *uname,
			   __attribute__((unused))const char *devicename,
			   const int flags)
{
  char		target[PATH_MAX] = {0};

  strcat(target, MOUNT_POINT);
  strcat(target, uname);
  strcat(target, "/pamelaRose");
  printf("pamelaRose: Unmounting %s\n", target);
  if (umount2(target, MNT_FORCE) == -1)
    {
      err_msg(ERR_UMOUNT, flags + ERRNO_FLAG);
      return 1;
    }
  return 0;
}

int	do_mkfs(const char*name,
		const int flags)
{
  char	*args[4];

  args[0] = strdup(MKFS_ARG0);
  args[1] = strdup(MKFS_ARG1);
  args[2] = concat_and_alloc(MAPPER, name);
  args[3] = 0;

  return execute_file(MKFS_PATH,
		      3,
		      args,
		      flags);
}

int	pam_mkfs(const char *name,
		 const int flags)
{
  pid_t	pid;
  int	res;

  putstring(MSG_MKFS);
  pid = fork();
  if (!pid)
    {
      res = do_mkfs(name, flags);
      exit(res);
    }
  waitpid(pid, &res, 0);
  return res;
}
