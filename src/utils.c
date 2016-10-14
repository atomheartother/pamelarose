/*
** utils.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:56 2016 Thomas Navennec
** Last update Fri Oct 14 17:08:01 2016 Thomas Navennec
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include <stdio.h>
/*
** Generic error msg function
*/
void	err_msg(const char * const msg, const int flags)
{
  if (flags == PAM_SILENT)
    return ;
  printf("Errror: %s\n", msg);
}

/*
** Returns an allocated string
** containing the full path to the encrypted volume
*/
char	*get_crypt_path(pam_handle_t *pamh, const int flags)
{
  const char	*usrname;
  char		*path;
  int		res;

  res = pam_get_user(pamh, &usrname, NULL);
  if (res == PAM_SYSTEM_ERR || PAM_CONV_ERR)
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
