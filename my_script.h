/*
** my_script.h for my_script.h in /home/thibauj/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 15:07:44 2014 thibau_j
** Last update Sat Mar  1 17:30:59 2014 thibau_j
*/

#ifndef _MY_SCRIPT_
# define _MY_SCRIPT_

# define _XOPEN_SOURCE 500
# define __USE_BSD
# define _BSD_SOURCE

# include		<sys/select.h>
# include		<termios.h>
# include		<stdlib.h>
# include		<sys/types.h>
# include		<sys/stat.h>
# include		<fcntl.h>
# include		<unistd.h>
# include		<sys/ioctl.h>
# include		<stdlib.h>
# include		<stdio.h>
# include		<errno.h>
# include		<time.h>
# include		<string.h>

typedef struct		s_option
{
  char			a;
  char			time;
}			t_option;

typedef struct		s_output
{
  char			*filename;
  int			fdOutput;
  char			*shell;
}			t_output;

typedef struct		s_script
{
  struct s_option	*option;
  struct s_output	*output;
  struct termios	slave_term;
  struct termios	new_term;
  struct termios	save;
  int			master;
  int			slave;
}			t_script;

/*
** fctMyScript.c
*/

int			my_posix_openpt(int flags);
int			my_unlockpt(int fd);
char			*my_ptsname(int fd);
void			signal_mod(struct termios *termios_p, int fd);
void			my_grantpt(int fd);

/*
** fctSecure.c
*/

int			my_open(char *path, int flag);
int			my_read(int fd, void *buff, size_t count, t_script
				*script);
void			my_close(int fd);
void			my_dup(int fd);
int			my_ioctl(int fd, int flag, int fd2);

/*
** parsing.c
*/

void			init_option(t_option *option, char **args,
				    t_output *output);

/*
** my_script.c
*/

void			my_script(t_script *script);

#endif /* !MY_SCRIPT */
