/*
** open_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 16:01:38 2016 Thomas Navennec
** Last update Wed Oct 19 13:24:55 2016 Thomas Navennec
*/

#include <stdlib.h>
#include <stdio.h>
#include "open_container.h"
#include "utils.h"
#include "cryptsetup.h"
#include "mount_operations.h"

int	open_container(char *path, const char *uname, int flags)
{
  char	*name;
  int	res;

  if (!(name = get_crypt_name(uname, flags)))
    return 1;
  printf(PAM_OPEN, path);
  res = activate_file(path, name, flags); /* LUKSopen failed */
  if (res)
    putstring(PAM_NOOPEN);
  else
    res = pam_mount(uname, name, flags);
  free(name);
  return res;
}
