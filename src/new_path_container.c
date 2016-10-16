/*
** new_path_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 17:10:44 2016 Thomas Navennec
** Last update Sun Oct 16 16:02:59 2016 Thomas Navennec
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "new_pam_container.h"
#include "utils.h"
#include "get_next_line.h"

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

char	*concat_and_alloc(const char * const s1, const char * const s2)
{
  char	*res;

  if (!(res = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
    return NULL;
  res[0] = 0;
  strcat(res, s1);
  strcat(res, s2);
  return res;
}

void	putstring(const char * const s)
{
  write(STDOUT_FILENO, s, strlen(s));
}

int	execute_file(char *exec, int argc,
		     char *args[], int flags)
{
  int		err = 0;
  int		i = 0;

  printf("\n%s:\n", exec);
  while (i < argc)
    {
      if (!args[i])
	{
	  err_msg(ERR_MALLOC, flags);
	  err = 1; /* Don't return yet, we need to free */
	}
	printf("  %d:%s\n", i, args[i]);
      i++;
    }
  if (!err)
    {
      if (execv(exec, args) == -1)
	{
	  err = 1;
	  err_msg(ERR_EXECV, flags);
	}
    }
  i = 0;
  while (i < 5)
    {
      if (args[i])
	free(args[i]);
      i++;
    }
  return err;
}

/*
** Returns 0 if everything went well
*/
int	create_file(char * path,
		    char *size,
		    int flags)
{
  char		*args[6];

  args[0] = strdup(DD_ARG0);
  args[1] = strdup(DD_ARG1);
  args[2] = concat_and_alloc(DD_ARG2, path);
  args[3] = strdup(DD_ARG3);
  args[4] = concat_and_alloc(DD_ARG4, size);
  args[5] = 0;
  free(path);
  free(size);
  return execute_file(DD_EXE, 5, args, flags);
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
** Takes an existing file path and makes it a luks container
*/
int	encrypt_file(char *path, int flags)
{
  char	*args[5];

  args[0] = strdup(CR_ARG0);
  args[1] = strdup(CR_ARG1);
  args[2] = strdup(CR_ARG2);
  args[3] = path;
  args[4] = 0;
  return execute_file(CR_EXE, 4, args, flags);
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
  if (!line || !strncasecmp("no", line, strlen(line)))
    return 2;
  if (!(line = get_container_size()))
    return 1;
  pid_t pid;
  int err;
  pid = fork();
  if (!pid)
    {
      err = create_file(path, line, flags);
      exit(err);
    }
  free(line);
  waitpid(pid, &err, 0);
  if (err)
    return err;
  pid = fork();
  if (!pid)
    {
      err = encrypt_file(path, flags);
      exit(err);
    }
  waitpid(pid, &err, 0);
  if (err) /* Cryptsetup failed */
    {
      unlink(path);
      err_msg(ERR_CRYPT, flags);
      return 1;
    }
  return 0;
}
