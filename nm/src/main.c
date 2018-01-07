/*
** main.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Mon Feb 13 11:17:34 2017 hazer
** Last update Tue Feb 21 15:59:14 2017 hazer
*/

#include "nm.h"

int	system_type(t_metadata *metadata)
{
  if (metadata->data64.elf->e_ident[EI_CLASS] == ELFCLASS32)
    return (do32bits(metadata));
  else if (metadata->data64.elf->e_ident[EI_CLASS] == ELFCLASS64)
    return (do64bits(metadata));
  return (cerr_ret("nm: File format not recognized\n", NM_ERR));
}

int	open_file(t_metadata *metadata, char *file)
{
  metadata->fd = -1;
  metadata->data64.file = file;

  if ((metadata->fd = open(file, O_RDONLY)) == NM_ERR)
    return (err_opening(file, NM_ERR));
  if ((metadata->data64.data = mmap(NULL, lseek(metadata->fd, 0, SEEK_END),
				    PROT_READ, MAP_SHARED, metadata->fd, 0)) == MAP_FAILED)
    return (cerr_ret("nm: mmap failed\n", NM_ERR));
  metadata->data64.end = (char *)metadata->data64.data + filesize(metadata->fd);

  if ((metadata->data64.elf = (Elf64_Ehdr*)metadata->data64.data) == NULL)
    return (cerr_ret("nm : Invalid pointer\n", NM_ERR));
  if ((void*)metadata->data64.elf >= (void*)metadata->data64.end)
    return (cerr_ret("nm : The file is truncated", NM_ERR));
  return (NM_OK);
}

int	my_nm(t_metadata *metadata, char *file)
{
  if (open_file(metadata, file) == NM_ERR)
    return (NM_ERR);
  if (system_type(metadata) == NM_ERR)
    return (NM_ERR);
  if (metadata->system == BIT64)
    nm64bit(&(metadata->data64));
  else if (metadata->system == BIT32)
    nm32bit(&(metadata->data32));
  if (metadata->fd != NM_ERR)
    close(metadata->fd);
  return (NM_OK);
}

int	main(int ac, char **av)
{
  int		i;
  t_metadata	metadata;

  metadata.return_value = NM_OK;
  if (ac == 1)
    if (my_nm(&metadata, "a.out") == NM_ERR)
      return (NM_ERR);
  for (i = 1; i < ac; i++)
    if (my_nm(&metadata, av[i]) == NM_ERR)
      metadata.return_value = NM_ERR;
  return (metadata.return_value);
}
