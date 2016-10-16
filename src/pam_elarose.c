/*
** pam_elarose.c for  in /home/navenn_t/Programmation/crypto/Pamela
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Sun Oct  9 18:25:25 2016 Thomas Navennec
** Last update Sun Oct 16 16:05:13 2016 Thomas Navennec
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

/*
** Called when user opens his session
*/
int	pam_sm_open_session(__attribute__((unused))pam_handle_t *pamh,
			    int flags,
			    __attribute__((unused))int argc,
			    __attribute__((unused))const char **argv)
{
  char	*path;
  struct stat buf;
  int	res;

  if (!(path = get_crypt_path(flags)))
    return PAM_SESSION_ERR;
  res = stat(path, &buf);
  if (res == -1)
    {
      if (errno == ENOENT)
	{
	  if (new_pam_container(path, flags) == -1) /* No container was created */
	    {
	      free(path);
	      return (PAM_SESSION_ERR);
	    }
	}
      else
	{
	  err_msg(ERR_STAT, flags);
	  free(path);
	  return PAM_SESSION_ERR;
	}
    }
  /* access_container(pamh, path, flags); */
  free(path);
  return (PAM_SUCCESS);
}

/*
** Called when user closes his session
*/
int pam_sm_close_session(__attribute__((unused))pam_handle_t *pamh,
			 int flags,
			 __attribute__((unused))int argc,
			 __attribute__((unused))const char **argv)
{
  char	*path;
  struct stat buf;
  int	res;

  if (!(path = get_crypt_path(flags)))
    return PAM_SESSION_ERR;
  res = stat(path, &buf);
  if (res == -1)
    {
      free(path);
      return PAM_SESSION_ERR;
    }
  /* close_container(pamh, path, flags); */
  free(path);
  return (PAM_SUCCESS);
}

