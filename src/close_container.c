#include <stdlib.h>
#include "utils.h"
#include "cryptsetup.h"
#include "mount_operations.h"

/*
** Closes the container
** Unmounts it before closing if asked to
*/
int	close_container(char * path, const char *uname, int flags)
{
  char	*name;
  int	res = 0;

  if (!(name = get_crypt_name(uname, flags)))
    return 1;
  if (flags & UMOUNT_FLAG)
    res = pam_umount(uname, name, flags);
  if (!res)
    res = deactivate_file(path, name, flags) > 0;
  free(name);
  return res;
}
