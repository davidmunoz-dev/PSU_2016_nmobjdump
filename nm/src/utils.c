/*
** utils.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:49:18 2017 hazer
** Last update Tue Feb 21 15:59:46 2017 hazer
*/

#include "nm.h"

char		get_type(int type, int flags, int info, int value)
{
  char        res;

  res = 'U';
  if (type == SHT_NOBITS && flags == (SHF_WRITE + SHF_ALLOC))
    res = 'B';
  if ( (type == SHT_PROGBITS || type == SHT_DYNAMIC)
       && flags == (SHF_WRITE + SHF_ALLOC))
    res = 'D';
  if (type == SHT_PROGBITS && flags == (SHF_ALLOC + SHF_EXECINSTR))
    res = 'T';
  if (type == SHT_PROGBITS && flags == SHF_ALLOC)
    res = 'R';
  if (ELF64_ST_BIND(info) == STB_WEAK)
    res = 'W';
  if (type > SHT_DYNSYM)
    res = 'T';
  if ((ELF64_ST_BIND(info) == STB_LOCAL || value == 0) && res != 'U')
    res += 32;
  return (res);
}

int             get_greater(char *str1, char *str2)
{
  if (str1 == NULL)
    return (2);
  if (*str1 <= 32)
    return (2);
  if (*str2 <= 32)
    return (1);
  while (*str1 || *str2)
    {
      if (*str1 < *str2)
	return (1);
      if (*str1 > *str2)
	return (2);
      str1++;
      str2++;
    }
  return (NM_OK);
}

int		filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}
