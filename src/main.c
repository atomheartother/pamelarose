/*
** main.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Tue Oct 18 08:54:43 2016 Thomas Navennec
** Last update Tue Oct 18 10:06:04 2016 Thomas Navennec
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "open_container.h"
#include "close_container.h"
#include "new_pam_container.h"

int	del_container(char *path, int flags)
{
  int	res;

  res = close_container(path, flags);
  if (res)
    return res;
  if (unlink(path))
    {
      err_msg(ERR_UNLINK, flags);
      res = 1;
    }
  return res;
}

int	handle_command(const char *str)
{
  char	*path = get_crypt_path(0);

  if (!path)
    return 1;

  const unsigned	count = 4;
  static int	(*func[4])(char *, int) = {
    &open_container, &close_container, &new_pam_container, &del_container};
  static char	*cmds[4] = {"open", "close", "create", "delete"};
  unsigned	i = 0;
  int		ret = 1;

  while (i < 4)
    {
      if (!strcmp(str, cmds[i]))
	{
	  ret = func[i](path, 0);
	  break ;
	}
      i++;
    }
  if (i == count)
    err_msg(PAM_USAGE, 0);
  free(path);
  return ret;
}

int	main(int ac, const char *av[])
{
  if (ac != 2)
    err_msg(PAM_USAGE, 0);
  else
    return handle_command(av[1]);
  return 1;
}
