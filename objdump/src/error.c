/*
** error.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Tue Feb 14 17:47:08 2017 hazer
** Last update Mon Feb 20 15:28:23 2017 hazer
*/

#include "objdump.h"

int	err_opening(char *file, int err)
{
  if (file == NULL)
    printf("objdump: « a.out»: No such file\n");
  else
    printf("objdump: «%s»: No such file\n", file);
  return (err);
}

void	cerr_exit(char *str, int err)
{
  write(1, str, strlen(str));
  exit(err);
}

int	cerr_ret(char *str, int err)
{
  write(1, str, strlen(str));
  return (err);
}
