#ifndef DEL_CONTAINER_H_
# define DEL_CONTAINER_H_

# define ERR_DELET	"Failed to delete file"
# define PAM_DELETED	"Container deleted\n"

int	del_container(char *path, const char *uname, int flags);

#endif
