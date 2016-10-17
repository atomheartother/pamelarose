/*
** open_container.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 16:01:36 2016 Thomas Navennec
** Last update Mon Oct 17 16:25:42 2016 Thomas Navennec
*/

#ifndef OPEN_CONTAINER_H_
# define OPEN_CONTAINER_H_

# define ERR_LOPEN	"Could not open encrypted device"

# define PAM_OPEN	"** PAMelaRose container opening **\n"

int	open_container(char *path, int flags);

#endif