/*
** cryptsetup.c for  in /home/navenn_t/Programmation/crypto/pamelarose/src
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 13:19:04 2016 Thomas Navennec
** Last update Mon Oct 17 14:15:22 2016 Thomas Navennec
*/

#include <libcryptsetup.h>
#include "utils.h"

int	format_file(const char *path, int flags)
{
  struct crypt_device	*cd;

  if (crypt_init(&cd, path) < 0)
    {
      err_msg(ERR_CRINIT, flags);
      return 1;
    }
  struct crypt_params_luks1 param;
  param.hash = CR_HASH;
  params.data_alignment = 0;
  params.data_device = NULL;

  if (crypt_format(cd, CRYPT_LUKS1, CR_CIPHER,
		   NULL, NULL, CR_KEY / 8, &params))
    {
      err_msg(ERR_CRFORM, flags);
      crypt_free(cd);
      return 1;
    }
}
