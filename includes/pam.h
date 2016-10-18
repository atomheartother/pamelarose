#ifndef PAM_H_
# define PAM_H_

# include <security/pam_modules.h>

# define ERR_UNAME	"Could not get username"

int	get_pam_uname(pam_handle_t *pamh,
		      const char **name,
		      int flags);

#endif
