/*
** new_path_container.c for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Fri Oct 14 17:10:44 2016 Thomas Navennec
** Last update Fri Oct 14 18:48:08 2016 Thomas Navennec
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

/*
** Returns 0 if everything went well
*/
int	create_file(char * path,
		    char *size,
		    int flags)
{
  char	*args[6];
  unsigned	i = 0;
  int		err = 0;

  args[0] = strdup("dd");
  args[1] = strdup("if=/dev/urandom");
  args[2] = concat_and_alloc("of=", path);
  args[3] = strdup("bs=1M");
  args[4] = concat_and_alloc("count=", size);
  args[5] = 0;
  while (i < 5)
    {
      if (!args[i])
	{
	  err_msg(ERR_MALLOC, flags);
	  err = -1; /* Don't return yet, we need to free */
	}
      i++;
    }
  if (!err)
    {
    if (execv("/bin/dd", args) == -1)
      {
      	err = -2;
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
  free(path);
  free(size);
  return err;
}

/*
** Returns -1 if container was not created
** 0 otherwise
*/
int	new_pam_container(pam_handle_t *pamh,
			    char * path,
			    int flags)
{
  char *line;
  putstring(NEWPAM_WELCOME);
  putstring(NEWPAM_PROMPT);
  line = get_next_line(STDIN_FILENO);
  if (!line || !strncasecmp("no", line, strlen(line)))
    return -1;
  int	loop = NEWPAM_MAX_TRIES;
  while (loop > 0)
    {
      putstring(NEWPAM_SIZE);
      line = get_next_line(STDIN_FILENO);
      if (!line)
	return -1;
      if (!check_nums(line)) /* Valid input */
	loop = -1;
      else
	{
	  free(line);
	  puts(NEWPAM_ERR);
	  loop--;
	}
    }
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
  if (!err)
    printf("%s %s\n", NEWPAM_DONE, path);
  return err;
}
