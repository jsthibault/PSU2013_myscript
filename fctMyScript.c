/*
** fctMyScript.c for fct in /home/thibauj/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 15:05:54 2014 thibau_j
** Last update Sat Mar  1 17:30:08 2014 thibau_j
*/

#include "my_script.h"

int		my_posix_openpt(int flags)
{
  int		fd;

  if ((fd = open("/dev/ptmx", flags)) == -1)
    exit(EXIT_FAILURE);
  return (fd);
}

int		my_unlockpt(int fd)
{
  int		unlock;
  int		res;

  unlock = 0;
  if ((res = ioctl(fd, TIOCSPTLCK, &unlock)) == -1)
    exit(EXIT_FAILURE);
  return (res);
}

char		*my_ptsname(int fd)
{
  static char	*name = NULL;
  int		i;

  if (name == NULL)
    {
      name = malloc(sizeof(char) * 16);
      if (name == NULL)
	exit(EXIT_FAILURE);
    }
  if (ioctl(fd, TIOCGPTN, &i) == -1)
    exit(EXIT_FAILURE);
  sprintf(name, "/dev/pts/%i", i);
  return (name);
}

void			my_grantpt(int fd)
{
  if (fchmod(fd, 0620) == -1)
    exit(EXIT_FAILURE);
}

void			signal_mod(struct termios *termios_p, int fd)
{
  termios_p->c_lflag &= ~(ECHO | ICANON | ISIG);
  termios_p->c_cc[VMIN] = 1;
  termios_p->c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSANOW, termios_p) == -1)
    exit(EXIT_FAILURE);
}
