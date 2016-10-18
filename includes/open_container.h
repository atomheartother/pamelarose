/*
** open_container.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 16:01:36 2016 Thomas Navennec
** Last update Tue Oct 18 10:41:44 2016 Thomas Navennec
*/

#ifndef OPEN_CONTAINER_H_
# define OPEN_CONTAINER_H_

# define ERR_LOPEN	"Could not open encrypted device"

# define PAM_OPEN	"** PAMelaRose: opening %s **\n"
# define PAM_NOOPEN	"Container was not opened\n"

int	open_container(char *path, const char *uname, int flags);

#endif
