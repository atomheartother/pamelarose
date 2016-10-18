/*
** open_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 16:01:38 2016 Thomas Navennec
** Last update Tue Oct 18 17:15:07 2016 Thomas Navennec
*/

#include <stdlib.h>
#include <stdio.h>
#include "open_container.h"
#include "utils.h"
#include "cryptsetup.h"

int	open_container(char *path, int flags)
{
  char	*name;
  int	res;

  if (!(name = get_crypt_name(flags)))
    return 1;
  printf(PAM_OPEN, path);
  res = activate_file(path, name, flags); /* LUKSopen failed */
  if (res)
    putstring(PAM_NOOPEN);
  free(name);
  return res;
}
