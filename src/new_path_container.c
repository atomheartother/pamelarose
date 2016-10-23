#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "new_pam_container.h"
#include "utils.h"
#include "get_next_line.h"
#include "cryptsetup.h"
#include "open_container.h"

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

/*
** Writes percentage progress
*/
void	write_percentage(int p)
{
  char	percent[strlen(PER_STR) + 5];
  int	tens = 10;

  
  while (p / tens)
    tens *= 10;
  percent[0] = 0;
  strcat(percent, PER_STR);
  unsigned i = strlen(PER_STR);
  tens /= 10;
  while (tens)
    {
      percent[i++] = ((p / tens) % 10) + '0';
      tens /= 10;
    }
  percent[i++] = '%';
  percent[i] = 0;
  putstring(percent);
}

/*
** Creates the file and displays a % progress
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
      err_msg(path, flags);
      return 1;
    }
  while (*size)
    {
      count = count * 10 + ((*size) - '0');
      size++;
    }
  srandom(time(NULL));
  int total = count;
  while (count > 0)
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
	  close(fd);
	  return 1;
	}
      write_percentage((total - count) * 100 / total);
      count--;
    }
  write_percentage(100);
  putstring("\n");
  close(fd);
  return 0;
}

/*
** Ask user for the size of the container
*/
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
** Returns 1 if an error occured
** Returns 0 if a container was created succesfully, or if the user
** did not want a container to be created
*/
int	new_pam_container(char * path,
			  __attribute__((unused))const char * uname,
			  int flags)
{
  /*
  ** Check that there is no container
  */
  struct stat buf;
  if (!stat(path, &buf))
    {
      err_msg(ERR_BADCREA, flags);
      return 1;
    }
  putstring(NEWPAM_WELCOME);
  putstring(NEWPAM_PROMPT);
  /*
  ** Ask the user if they want to create a container
  */
  char *line;
  line = get_next_line(STDIN_FILENO);
  if (!line || (strlen(line) &&
		!strncasecmp("no", line, strlen(line))))
    return 0;
  free(line);
  /*
  ** Ask the user for the container's size
  */
  if (!(line = get_container_size()))
    return 1;
  /*
  ** Create the file
  */
  int	err = create_file(path, line, flags);
  free(line);
  if (err)
    return err;
  /*
  ** Encrypt the file
  */
  if (format_file(path, flags)) /* Cryptsetup failed */
    {
      unlink(path);
      return 1;
    }
  /*
  ** We proceed to first open, which also performs MKFS
  ** Unset OPEN_FLAG since the open HAS to happen!
  */
  flags &= ~OPEN_FLAG;
  return open_container(path, uname, flags + MKFS_FLAG);
}
