#include <string.h>
#include <errno.h>
#include <libcryptsetup.h>
#include "cryptsetup.h"
#include "utils.h"
#include "get_next_line.h"

/*
** Create a LUKS-formatted file
*/
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
				      0, NULL, CRYPT_ACTIVATE_READONLY) < 0)
    {
      err_msg(ERR_KSLOT, flags);
      err = 1;
    }
  crypt_free(cd);
  return err;
}

/*
** luksOpen
*/
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
  ** If the device is already active, we don't have to activate it
  */
  if (crypt_status(cd, name) == CRYPT_ACTIVE)
    {
      crypt_free(cd);
      return 1;
    }

  /*
  ** Activate the device
  */
  int err = 0;
  if (crypt_activate_by_passphrase(cd, name, CRYPT_ANY_SLOT, NULL, 0,
				   0) < 0)
    {
      err_msg(ERR_CRACT, flags);
      err_msg(strerror(errno), flags);
      err = 1;
    }
  crypt_free(cd);
  return err;
}

/*
** Check if device is active
** returns  0 if it is active
** 1 if it is inactive
** 2 if an error occured
*/
int	is_active(const char *path, const char *name, int flags)
{
 struct crypt_device	*cd;
 int			res = 0;

  if (crypt_init(&cd, path) < 0)
    {
      err_msg(ERR_CRINIT, flags);
      return 2;
    }
  if (crypt_load(cd, CRYPT_LUKS1, NULL) < 0)
    {
      crypt_free(cd);
      err_msg(ERR_CRLOAD, flags);
      return 2;
    }
  int inf = crypt_status(cd, name);
  if (inf == CRYPT_INACTIVE || inf == CRYPT_INVALID)
    res = 1;
  crypt_free(cd);
  return res;
}

/*
** luksClose
*/
int	deactivate_file(const char *path, const char * name, int flags)
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
  ** If the device is not activated, we won't be able to deactivate it
  */
  if (crypt_status(cd, name) != CRYPT_ACTIVE)
    {
      crypt_free(cd);
      return 1;
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
