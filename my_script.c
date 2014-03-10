/*
** my_script.c for my_script.c in /home/thibau_j/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 12:24:49 2014 thibau_j
** Last update Sat Mar  1 17:32:59 2014 thibau_j
*/

#include "my_script.h"

static void	father_iocontrol(t_script *script, char bool)
{
  char		input[500];
  int		nb;
  time_t	t;

  if (bool == 0)
    {
      nb = my_read(0, input, sizeof(input), script);
      write(script->master, input, nb);
    }
  else
    {
      if (script->option->time == 1)
	{
	  if ((t = time(NULL)) == (time_t)-1)
	    exit(EXIT_FAILURE);
 	  sprintf(input, "Script started on %s", asctime(gmtime(&t)));
	  write(script->output->fdOutput, input, strlen(input));
	  script->option->time = 0;
	}
      nb = my_read(script->master, input, sizeof(input), script);
      write(1, input, nb);
      write(script->output->fdOutput, input, nb);
    }
}

static void	father_fork(t_script *script)
{
  fd_set	fd_in;
  int		i;

  i = 1;
  my_close(script->slave);
  while (i == 1)
    {
      FD_ZERO(&fd_in);
      FD_SET(0, &fd_in);
      FD_SET(script->master, &fd_in);
      if (select(script->slave, &fd_in, NULL, NULL, NULL) == -1)
	{
	  fprintf(stderr, "Error %d on select()\n", errno);
	  exit(1);
	}
      if (FD_ISSET(0, &fd_in) != 0)
	father_iocontrol(script, 0);
      if (FD_ISSET(script->master, &fd_in) != 0)
	father_iocontrol(script, 1);
    }
}

static void		child_fork(t_script *script)
{
  int			nb;
  char			*tab[1];

  *tab = NULL;
  my_close(script->master);
  if ((nb = tcgetattr(script->slave, &script->slave_term)) == -1)
    exit(EXIT_FAILURE);
  script->new_term = script->slave_term;
  cfmakeraw(&script->new_term);
  signal_mod(&(script->new_term), 0);
  my_close(0);
  my_close(1);
  my_close(2);
  my_dup(script->slave);
  my_dup(script->slave);
  my_dup(script->slave);
  my_close(script->slave);
  if (setsid() == (pid_t)-1)
    exit(EXIT_FAILURE);
  if (ioctl(0, TIOCSCTTY, 1) == -1)
    exit(EXIT_FAILURE);
  if (execvp(script->output->shell, tab) == -1)
    exit(EXIT_FAILURE);
}

static void	fork_this(t_script *script)
{
  script->master = my_posix_openpt(O_RDWR);
  my_unlockpt(script->master);
  script->slave = my_open(my_ptsname(script->master), O_RDWR);
  my_grantpt(script->slave);
  if (script->slave < 0)
    {
      fprintf(stderr, "Error happened.\n");
      exit(EXIT_FAILURE);
    }
  if (fork() != 0)
    {
      father_fork(script);
    }
  else
    {
      child_fork(script);
    }
}

void			my_script(t_script *script)
{
  fork_this(script);
}
