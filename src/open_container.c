#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "open_container.h"
#include "utils.h"
#include "cryptsetup.h"
#include "mount_operations.h"
#include "close_container.h"
#include "get_next_line.h"

int	open_container(char *path, const char *uname, int flags)
{
  char	*name;
  int	res = 0;
  char *line;

  /*
  ** Ask the user if they want to open the container
  */
  if (flags & OPEN_FLAG)
    {
      putstring(OPEN_PROMPT);
      line = get_next_line(STDIN_FILENO);
      if (!line || (strlen(line) &&
		    !strncasecmp("no", line, strlen(line))))
	return 0;
      free(line);
    }

  /*
  ** Get device name
  */
  if (!(name = get_crypt_name(uname, flags)))
    return 1;

  /*
  ** Check that the container isn't already activated & mounted
  */
  if (!is_active(path, name, flags))
    {
      free(name);
      return 0;
    }

  /*
  ** luksOpen
  */
  printf(PAM_OPEN, path);
  res = activate_file(path, name, flags); /* LUKSopen failed */
  if (res)
    putstring(PAM_NOOPEN);
  else
    {
      /*
      ** If we just created the container,
      ** we need to create the FileSystem
      */
      if (flags & MKFS_FLAG)
	res = pam_mkfs(name, flags);
      if (!res) /* If all went well, we mount */
	res = pam_mount(uname, name, flags);
    }
  free(name);
  return res;
}
