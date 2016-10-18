#include <security/pam_modules.h>
#include <utils.h>
#include "pam.h"

int	get_pam_uname(pam_handle_t *pamh,
		      const char **name,
		      int flags)
{
  int	res;

  res = pam_get_user(pamh, name, (void *)0);
  if (res == PAM_SYSTEM_ERR || res == PAM_CONV_ERR)
    {
      err_msg(ERR_UNAME, flags);
      return 1;
    }
  return 0;
}
