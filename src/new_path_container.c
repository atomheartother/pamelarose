/*
** new_path_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 17:10:44 2016 Thomas Navennec
** Last update Tue Oct 18 11:52:42 2016 Thomas Navennec
*/

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "new_pam_container.h"
#include "utils.h"
#include "get_next_line.h"
#include "cryptsetup.h"

int	check_nums(const char *input)
{
  if (!(*input))
    return -1;
  while (*input)
    {
      if (*input < '0' || *input > '9')
	return -1;
      input++;
    }
  return 0;
}

char	*concat_and_alloc(const char * const s1,
			  const char * const s2)
{
  char	*res;

  if (!(res = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
    return NULL;
  res[0] = 0;
  strcat(res, s1);
  strcat(res, s2);
  return res;
}

/*
** Returns 0 if everything went well
*/
int	create_file(char * path,
		    char *size,
		    int flags)
{
  int	count = 0;
  int	fd;

  fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd == -1)
    {
      err_msg(ERR_CREAT, flags);
      return 1;
    }
  while (*size)
    {
      count = count * 10 + ((*size) - '0');
      size++;
    }
  printf("Writing %dMB\n", count);
  srandom(time(NULL));
  while (count)
    {
      char block[BLOCK_SIZE] = {0};
      unsigned i = 0;
      while (i < BLOCK_SIZE)
	{
	  char c = (random() % 256) - 127;
	  block[i++] = c;
	}
      if (write(fd, block, BLOCK_SIZE) == -1)
	{
	  err_msg(BAD_WRITE, flags);
	  return 1;
	}
      count--;
    }
  return 0;
}

char	*get_container_size()
{
  int	loop = NEWPAM_MAX_TRIES;
  char	*line;

  while (loop > 0)
    {
      putstring(NEWPAM_SIZE);
      line = get_next_line(STDIN_FILENO);
      if (!line)
	return NULL;
      if (!check_nums(line)) /* Valid input */
	loop = -1;
      else
	{
	  free(line);
	  puts(NEWPAM_ERR);
	  loop--;
	}
    }
  return loop == 0 ? NULL : line;
}

/*
** Returns 2 if the user did not want to create a container
** Returns 1 if an error occured
** Returns 0 if a container was created succesfully
*/
int	new_pam_container(char * path,
			  int flags)
{
  char *line;
  putstring(NEWPAM_WELCOME);
  putstring(NEWPAM_PROMPT);
  line = get_next_line(STDIN_FILENO);
  if (!line || (strlen(line) &&
		!strncasecmp("no", line, strlen(line))))
    return 2;
  free(line);
  if (!(line = get_container_size()))
    return 1;
  int	err = create_file(path, line, flags);
  if (err)
    return err;
  return 0;
  if (format_file(path, flags)) /* Cryptsetup failed */
    {
      unlink(path);
      return 1;
    }
  return 0;
}
