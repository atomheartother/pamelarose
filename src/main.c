#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "open_container.h"
#include "close_container.h"
#include "new_pam_container.h"

/*
** The code here lets root user manage containers
*/

int	del_container(char *path, const char *uname, int flags)
{
  int	res = 0;

  res = close_container(path, uname, 0x8000U + UMOUNT_FLAG);
  if (unlink(path))
    {
      err_msg(ERR_UNLINK, flags);
      res = 1;
    }
  else
    putstring(PAM_DELETED);
  return res;
}

int	handle_command(const char *str, const char *uname)
{
  char	*path = get_crypt_path(uname, 0);
  if (!path)
    return 1;
  setuid(0);
  const unsigned	count = 4;
  static int	(*func[4])(char *, const char *, int) = {
    &open_container, &close_container, &new_pam_container, &del_container};
  static char	*cmds[4] = {"open", "close", "create", "delete"};
  unsigned	i = 0;
  int		ret = 1;

  while (i < 4)
    {
      if (!strcmp(str, cmds[i]))
	{
	  ret = func[i](path, uname, UMOUNT_FLAG);
	  break ;
	}
      i++;
    }
  if (i == count)
    err_msg(PAM_USAGE, 0);
  free(path);
  return ret;
}

int	check_uname(const char *uname)
{
  struct passwd *pw = getpwnam(uname);

  return (pw == (struct passwd *)0 || !pw->pw_uid);
}

int	main(int ac, const char *av[])
{
  if (getuid())
    {
      err_msg(ROOTREQ, 0);
      return 1;
    }
  if (ac != 3)
    err_msg(PAM_USAGE, 0);
  else
    {
      if (check_uname(av[1]))
	{
	  err_msg(PAM_BADUNAME, 0);
	  return 1;
	}
      return handle_command(av[2], av[1]);
    }
  return 1;
}
