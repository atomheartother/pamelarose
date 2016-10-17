/*
** cryptsetup.c for  in /home/navenn_t/Programmation/crypto/pamelarose/src
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 13:19:04 2016 Thomas Navennec
** Last update Mon Oct 17 18:24:55 2016 Thomas Navennec
*/

#include <libcryptsetup.h>
#include "cryptsetup.h"
#include "utils.h"
#include "get_next_line.h"

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
  param.data_alignment = 0;
  param.data_device = NULL;

  if (crypt_format(cd, CRYPT_LUKS1, CR_CIPHER, CR_BLOCKMODE,
		   NULL, NULL, CR_KEY / 8, &param))
    {
      err_msg(ERR_CRFORM, flags);
      crypt_free(cd);
      return 1;
    }
  int			err = 0;
  if (crypt_keyslot_add_by_volume_key(cd, CRYPT_ANY_SLOT, NULL,
				      0, NULL, 0) < 0)
    {
      err_msg(ERR_KSLOT, flags);
      err = 1;
    }
  crypt_free(cd);
  return err;
}

int	activate_file(const char *path, const char *name, int flags)
{
  struct crypt_device	*cd;

  if (crypt_init(&cd, path) < 0)
    {
      err_msg(ERR_CRINIT, flags);
      return 1;
    }
  if (crypt_load(cd, CRYPT_LUKS1, NULL) < 0)
    {
      crypt_free(cd);
      err_msg(ERR_CRLOAD, flags);
      return 1;
    }
  /*
  ** If the device is anything but inactive, don't perform any action on it
  ** It could be busy or corrupt or already active, either way.
  */
  if (crypt_status(cd, name) != CRYPT_INACTIVE)
    {
      crypt_free(cd);
      return 0;
    }

  /*
  ** Activate the device
  */
  int err = 0;
  if (crypt_activate_by_passphrase(cd, name, CRYPT_ANY_SLOT, NULL, 0,
				   CRYPT_ACTIVATE_READONLY) < 0)
    {
      err_msg(ERR_CRACT, flags);
      err = 1;
    }
  crypt_free(cd);
  return err;
}

int	deactivate_file(const char * name, int flags)
{
  struct crypt_device	*cd;

  if (crypt_init_by_name(&cd, name) < 0)
    {
      err_msg(ERR_CRINIT, flags);
      return 1;
    }
  /*
  ** If the device is not activated, we won't be able to deactivate it
  */
  if (crypt_status(cd, name) != CRYPT_ACTIVE)
    {
      crypt_free(cd);
      return 0;
    }
  int	err = 0;
  if (crypt_deactivate(cd, name) < 0)
    {
      err_msg(ERR_DEACT, flags);
      err = 1;
    }
  crypt_free(cd);
  return err;
}
