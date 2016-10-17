/*
** utils.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 15:24:56 2016 Thomas Navennec
** Last update Mon Oct 17 15:31:03 2016 Thomas Navennec
*/

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <security/pam_modules.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void	putstring(const char * const s)
{
  write(STDOUT_FILENO, s, strlen(s));
}

/*
** Generic error msg function
*/
void	err_msg(const char * const msg, const int flags)
{
  if (flags == PAM_SILENT)
    return ;
  fprintf(stderr, "Error: %s\n", msg);
}

int	execute_file(char *exec, int argc,
		     char *args[], int flags)
{
  int		err = 0;
  int		i = 0;

  while (i < argc) /* Check Mallocs */
    {
      if (!args[i])
	{
	  err_msg(ERR_MALLOC, flags);
	  err = 1; /* Don't return yet, we need to free */
	}
      i++;
    }
  if (!err)
    {
      if (execv(exec, args) == -1)
	{
	  err = 1;
	  err_msg(ERR_EXECV, flags);
	}
    }
  i = 0;
  while (i < 5)
    {
      if (args[i])
	free(args[i]);
      i++;
    }
  return err;
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
