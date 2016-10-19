/*
** mount_operations.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Wed Oct 19 10:27:52 2016 Thomas Navennec
** Last update Wed Oct 19 10:53:32 2016 Thomas Navennec
*/

#ifndef MOUNT_OPERATIONS_H_
# define MOUNT_OPERATIONS_H_

int	mount(const char *uname,
	      const char *devicename);
int	umount(const char *uname,
	       const char *devicename);

#endif
