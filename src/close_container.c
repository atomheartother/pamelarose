/*
** close_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 18:34:45 2016 Thomas Navennec
** Last update Mon Oct 17 18:40:44 2016 Thomas Navennec
*/

#include <stdlib.h>
#include "utils.h"
#include "cryptsetup.h"

int	close_container(int flags)
{
  char	*name;
  int	res;

  if (!(name = get_crypt_name(flags)))
    return 1;
  res = deactivate_file(name, flags) > 0;
  free(name);
  return res;
}
