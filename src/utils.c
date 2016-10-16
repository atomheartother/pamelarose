/*
** utils.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:56 2016 Thomas Navennec
** Last update Sun Oct 16 16:03:13 2016 Thomas Navennec
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

/*
** Generic error msg function
*/
void	err_msg(const char * const msg, const int flags)
{
  if (flags == PAM_SILENT)
    return ;
  fprintf(stderr, "Errror: %s\n", msg);
}

/*
** Returns an allocated string
** containing the full path to the encrypted volume
*/
char	*get_crypt_path(const int flags)
{
  char	usrname[LOGIN_NAME_MAX + 1];
  char		*path;
  int		res;

  res = getlogin_r(usrname, LOGIN_NAME_MAX + 1);
  if (res)
    {
      err_msg(ERR_UNAME, flags);
      return NULL;
    }
  const size_t len = strlen(PATH_ROOT) + strlen(usrname) +
    strlen(FILE_PREFIX) + strlen(FILE_NAME);
  if (!(path = malloc(sizeof(char) * (len + 1))))
    {
      err_msg(ERR_MALLOC, flags);
      return NULL;
    }
  path[0] = 0;
  strcat(path, PATH_ROOT);
  strcat(path, usrname);
  strcat(path, FILE_PREFIX);
  strcat(path, FILE_NAME);
  return path;
}
