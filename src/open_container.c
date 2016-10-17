/*
** open_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 16:01:38 2016 Thomas Navennec
** Last update Mon Oct 17 16:25:44 2016 Thomas Navennec
*/

#include "open_container.h"
#include "utils.h"
#include "cryptsetup.h"

int	open_container(char *path, int flags)
{
  putstring(PAM_OPEN);
  if (activate_file(path, flags)) /* LUKSopen failed */
    {
      err_msg(ERR_LOPEN, flags);
      return 1;
    }
}
