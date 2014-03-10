/*
** parsing.c for parsing in /home/thibauj/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 15:08:08 2014 thibau_j
** Last update Thu Feb 27 15:08:09 2014 thibau_j
*/

#include "my_script.h"

static int		parse_option(char *target, char **arg, char *search)
{
  int			i;

  i = 0;
  while (arg[i] != NULL)
    {
      if (strcmp(arg[i], search) == 0)
	{
	  *target = 1;
	  return (i);
	}
      i = i + 1;
    }
  return (-1);
}

static int		option_statue(char *str)
{
  if (str != NULL && str[0] != '\0')
    {
      if (str[0] != '-')
	return (1);
      return (-1);
    }
  return (-1);
}

static char		*give_filename(char **args)
{
  int			i;

  i = 0;
  while (args[i] != NULL)
    {
      if (i != 0 && option_statue(args[i]) == 1)
	return (args[i]);
      i = i + 1;
    }
  return ("typescript");
}

void			init_option(t_option *option, char **args,
				    t_output *output)
{
  int			i;

  i = 0;
  option->a = 0;
  output->fdOutput = 0;
  output->filename = give_filename(args);
  output->shell = getenv("SHELL");
  option->time = 1;
  if (output->shell == NULL)
    output->shell = "sh";
  if ((i = parse_option(&(option->a), args, "-a")) != -1)
    option->a = 1;
}
