/*
** Tell PAM that we're managing a session
*/
#define PAM_SM_SESSION

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include "utils.h"
#include "new_pam_container.h"
#include "open_container.h"
#include "close_container.h"
#include "pam.h"

int	user_is_root(const char * name)
{
  struct passwd *pw = getpwnam(name);

  return pw->pw_uid == 0;
}

/*
** Called when user opens his session
*/
int	pam_sm_open_session(pam_handle_t *pamh,
			    int flags,
			    __attribute__((unused))int argc,
			    __attribute__((unused))const char **argv)
{
  const char  *name;
  char	*path;
  struct stat buf;
  int	res;

  if (get_pam_uname(pamh, &name, flags))
    return PAM_SESSION_ERR;
  if (user_is_root(name))
    return PAM_SUCCESS;
  if (!(path = get_crypt_path(name, flags)))
    return PAM_SESSION_ERR;
  res = stat(path, &buf);
  if (res == -1)
    {
      if (errno == ENOENT) /* If the container doesn't exist */
	{
	  res = new_pam_container(path, name, flags); /* Create and configure it */
	  free(path);
	  return (!res ? PAM_SUCCESS : PAM_SESSION_ERR);
	}
      else
	{
	  err_msg(ERR_STAT, flags);
	  free(path);
	  return PAM_SESSION_ERR;
	}
    }
  else
    {
      flags |= OPEN_FLAG;
      res = open_container(path, name, flags);
    }
  free(path);
  return (res ? PAM_SESSION_ERR : PAM_SUCCESS);
}

/*
** Called when user closes his session
*/
int pam_sm_close_session(pam_handle_t *pamh,
			 int flags,
			 __attribute__((unused))int argc,
			 __attribute__((unused))const char **argv)
{
  const char *name;
  char	*path;
  struct stat buf;
  int	res;

  if (get_pam_uname(pamh, &name, flags))
    return PAM_SESSION_ERR;
  if (!(path = get_crypt_path(name, flags)))
    return PAM_SESSION_ERR;
  res = stat(path, &buf);
  if (res == -1)
    {
      free(path);
      return PAM_SESSION_ERR;
    }
  flags |= UMOUNT_FLAG;
  res = close_container(path, name, flags);
  free(path);
  return (res ? PAM_SESSION_ERR : PAM_SUCCESS);
}

