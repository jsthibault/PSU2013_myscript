/*
** fctSecure.c for fct in /home/thibauj/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 15:05:45 2014 thibau_j
** Last update Sat Mar  1 16:42:12 2014 thibau_j
*/

#include "my_script.h"

int		my_open(char *path, int flag)
{
  int		fd;

  if ((fd = open(path, flag)) == -1)
    {
      fprintf(stderr, "Error on %s.\n", path);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

int		my_read(int fd, void *buff, size_t count, t_script *script)
{
  int		res;
  time_t	t;
  char		input[500];

  if ((t = time(NULL)) == (time_t)-1)
    exit(EXIT_FAILURE);
  res = read(fd, buff, count);
  if (res == 0)
    {
      tcsetattr(0, TCSANOW, &script->save);
      sprintf(input, "Script finished on %s\n", asctime(gmtime(&t)));
      write(script->output->fdOutput, input, strlen(input));
      printf("exit\nScript done, file is %s\n", script->output->filename);
      exit(EXIT_FAILURE);
    }
  if (res == -1)
    {
      tcsetattr(0, TCSANOW, &script->save);
      sprintf(input, "Script finished on %s\n", asctime(gmtime(&t)));
      write(script->output->fdOutput, input, strlen(input));
      printf("Script done, file is %s\n", script->output->filename);
      exit(EXIT_FAILURE);
    }
  return (res);
}

void		my_close(int fd)
{
  if (close(fd) == -1)
    exit(EXIT_FAILURE);
}

void		my_dup(int fd)
{
  if (dup(fd) == -1)
    exit(EXIT_FAILURE);
}

int 		my_ioctl(int fd, int flag, int fd2)
{
  int		res;

  if ((res = ioctl(fd, flag, fd2)) == -1)
    exit(EXIT_FAILURE);
  return (res);
}
