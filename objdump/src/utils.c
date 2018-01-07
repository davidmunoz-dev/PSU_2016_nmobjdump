/*
** utils.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:49:18 2017 hazer
** Last update Tue Feb 21 14:29:47 2017 hazer
*/

#include "objdump.h"

void	print_space(int i)
{
  int	a;

  for (a = 0; a < i; a++)
    printf(" ");
}

char	is_printable(char c)
{
  if (c >= ' ' && c <= '~')
    return (c);
  return ('.');
}

void	print_hexa(char str[16], int end)
{
  int           i;

  i = 0;
  print_space(2);
  while (i < 16)
    {
      if (i < end)
	printf("%c", is_printable(str[i]));
      else
	print_space(1);
      i++;
    }
  printf("\n");
}

void	print_sub(char str[16], unsigned int *hex,
		    char is_ok, int end, int i)
{
  int           space;

  space = 16 - end;
  space = space + (space / 4) + (16 - end);
  if (is_ok == 0)
    print_space(space);
  if (i != 0)
    print_hexa(str, end);
  if (is_ok == 1)
    {
      printf(" %04x ", *hex);
      *hex += 0x10;
    }
}

int	filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}
