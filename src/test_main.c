/*
** test_main.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 15:47:22 2016 Thomas Navennec
** Last update Mon Oct 17 16:51:55 2016 Thomas Navennec
*/

#include "cryptsetup.h"
#include <stdio.h>

int	main()
{
  if (!format_file("/home/navenn_t/zob", 0))
    {
      printf("Activation...\n");
      activate_file("/home/navenn_t/zob", 0);
    }
  return 0;
}
