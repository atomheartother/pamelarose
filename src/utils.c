#include <sys/types.h>
#include <pwd.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <security/pam_modules.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

/*
** Basic write() wrapper
*/
void	putstring(const char * const s)
{
  write(STDOUT_FILENO, s, strlen(s));
}

/*
** Generic error msg function,
** can be told to display errno
*/
void	err_msg(const char * const msg, const int flags)
{
  if (flags & PAM_SILENT)
    return ;
  fprintf(stderr, "PAMelaRose: %s\n", msg);
  if (flags & ERRNO_FLAG)
    fprintf(stderr, "PaAMelaRose: %s\n", strerror(errno));
}

/*
** Generic subprocess execution function
*/
int	execute_file(char *exec, int argc,
		     char *args[], const int flags)
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
  while (i < argc)
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
char	*get_crypt_path(const char *name, const int flags)
{
  char		*path;

  const size_t len = strlen(PATH_ROOT) + strlen(name) +
    strlen(FILE_PREFIX) + strlen(FILE_NAME);
  if (!(path = malloc(sizeof(char) * (len + 1))))
    {
      err_msg(ERR_MALLOC, flags);
      return NULL;
    }
  path[0] = 0;
  strcat(path, PATH_ROOT);
  strcat(path, name);
  strcat(path, FILE_PREFIX);
  strcat(path, FILE_NAME);
  return path;
}

/*
** Returns an allocate string containing
** the name the device should be mapped to
*/
char	*get_crypt_name(const char *uname, const int flags)
{
  char	*name;
  const size_t	len = strlen(uname) + strlen(NAME_STR);
  name = malloc(sizeof(char) * (len + 1));
  if (!name)
    {
      err_msg(ERR_MALLOC, flags);
      return NULL;
    }
  name[0] = 0;
  strcat(name, NAME_STR);
  strcat(name, uname);
  return name;
}

/*
** Generic concat function
*/
char	*concat_and_alloc(const char * const s1,
			  const char * const s2)
{
  char	*res;

  if (!(res = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
    return NULL;
  res[0] = 0;
  strcat(res, s1);
  strcat(res, s2);
  return res;
}
