#include <security/pam_modules.h>
#include <unistd.h>
#include "close_container.h"
#include "utils.h"
#include "del_container.h"

int	del_container(char *path, const char *uname, int flags)
{
  int	res = 0;

  flags |= PAM_SILENT;
  close_container(path, uname, flags);
  flags &= ~PAM_SILENT;
  if (unlink(path))
    {
      err_msg(ERR_DELET, flags);
      res = 1;
    }
  else
    putstring(PAM_DELETED);
  return res;
}
