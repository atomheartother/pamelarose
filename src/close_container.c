/*
** close_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 18:34:45 2016 Thomas Navennec
** Last update Wed Oct 19 13:33:47 2016 Thomas Navennec
*/

#include <stdlib.h>
#include "utils.h"
#include "cryptsetup.h"
#include "mount_operations.h"

int	close_container(char * path, const char *uname, int flags)
{
  char	*name;
  int	res;

  if (!(name = get_crypt_name(uname, flags)))
    return 1;
  res = pam_umount(uname, name, flags);
  if (!res)
    res = deactivate_file(path, name, flags) > 0;
  free(name);
  return res;
}
