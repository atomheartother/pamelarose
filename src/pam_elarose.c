/*
** pam_elarose.c for  in /home/navenn_t/Programmation/crypto/Pamela
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Sun Oct  9 18:25:25 2016 Thomas Navennec
** Last update Tue Oct 18 10:01:13 2016 Thomas Navennec
*/

/*
** Tell PAM that we're managing a session
*/
#define PAM_SM_SESSION

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"
#include "new_pam_container.h"
#include "open_container.h"
#include "close_container.h"
#include "pam.h"

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
  if (!(path = get_crypt_path(name, flags)))
    return PAM_SESSION_ERR;
  res = stat(path, &buf);
  if (res == -1)
    {
      if (errno == ENOENT)
	{
	  if ((res = new_pam_container(path, name, flags))) /* No container was created */
	    {
	      free(path);
	      return (res == 2 ? PAM_SUCCESS : PAM_SESSION_ERR);
	    }
	}
      else
	{
	  err_msg(ERR_STAT, flags);
	  free(path);
	  return PAM_SESSION_ERR;
	}
    }
  res = open_container(path, name, flags);
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
  res = close_container(path, name, flags);
  free(path);
  return (res ? PAM_SESSION_ERR : PAM_SUCCESS);
}

