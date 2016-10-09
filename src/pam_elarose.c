/*
** pam_elarose.c for  in /home/navenn_t/Programmation/crypto/Pamela
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Sun Oct  9 18:25:25 2016 Thomas Navennec
** Last update Sun Oct  9 18:28:39 2016 Thomas Navennec
*/

/*
** Tell PAM that we're managing a session
*/
#define PAM_SM_SESSION

#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh,
				   int flags,
				   int argc,
				   const char **argv)
{
  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh,
				    int flags,
				    int argc,
				    const char **argv)
{
  return (PAM_SUCCESS);
}

