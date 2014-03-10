/*
** main.c for main in /home/thibauj/rendu/PSU_2013_myscript
**
** Made by thibau_j
** Login   <thibau_j@epitech.net>
**
** Started on  Thu Feb 27 15:06:11 2014 thibau_j
** Last update Thu Feb 27 15:23:38 2014 thibau_j
*/

#include "my_script.h"

static void		init_struct(t_script *script, t_output *output,
				   t_option *option, char **args)
{
  init_option(option, args, output);

  if (tcgetattr(0, &script->save) == -1)
    exit(EXIT_FAILURE);
  script->option = option;
  script->output = output;
}

static void		start_script(t_script *script)
{
  if (script->option->a != 1)
    {
      script->output->fdOutput = my_open(script->output->filename,
					 O_RDWR | O_CREAT);
    }
  else
    {
      script->output->fdOutput = my_open(script->output->filename,
					 O_RDWR | O_APPEND);
    }
  if (fchmod(script->output->fdOutput, 00644) == -1)
    {
      printf("Fail to put right on %s.\n", script->output->filename);
      exit(EXIT_FAILURE);
    }
  my_script(script);
}

int			main(int __attribute__((unused))ac, char **av)
{
  t_option		option;
  t_output		output;
  t_script		script;

  init_struct(&script, &output, &option, av);
  start_script(&script);
  return (1);
}
