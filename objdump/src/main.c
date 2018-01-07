/*
** main.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Mon Feb 13 11:17:34 2017 hazer
** Last update Tue Feb 21 21:18:09 2017 hazer
*/

#include "objdump.h"

int	system_type(t_metadata *metadata)
{
  if (metadata->data64.elf->e_ident[EI_CLASS] == ELFCLASS32)
    return (do32bits(metadata));
  else if (metadata->data64.elf->e_ident[EI_CLASS] == ELFCLASS64)
    return (do64bits(metadata));
  return (cerr_ret("objdump: File format not recognized\n", OBJDUMP_ERR));
}

int	open_file(t_metadata *metadata, char *file)
{
  metadata->fd = -1;
  metadata->data64.file = file;

  if ((metadata->fd = open(file, O_RDONLY)) == OBJDUMP_ERR)
    return (err_opening(file, OBJDUMP_ERR));
  if ((metadata->data64.data = mmap(NULL, filesize(metadata->fd),
				    PROT_READ, MAP_SHARED, metadata->fd, 0)) == MAP_FAILED)
    return (cerr_ret("objdump: mmap failed\n", OBJDUMP_ERR));
  metadata->data64.end = (char *)metadata->data64.data + filesize(metadata->fd);
  if ((metadata->data64.elf = (Elf64_Ehdr*)metadata->data64.data) == NULL)
    return (cerr_ret("objdump: Invalid pointer\n", OBJDUMP_ERR));
  if ((void*)metadata->data64.elf >= (void*)metadata->data64.end)
    return (cerr_ret("objdump: The file is truncated", OBJDUMP_ERR));
  return (OBJDUMP_OK);
}

int	my_objdump(t_metadata *metadata, char *file)
{
  if (open_file(metadata, file) == OBJDUMP_ERR)
    return (OBJDUMP_ERR);
  if (system_type(metadata) == OBJDUMP_ERR)
    return (OBJDUMP_ERR);
  if (metadata->system == BIT64)
    objdump64bit(&(metadata->data64));
  else if (metadata->system == BIT32)
    objdump32bit(&(metadata->data32));
  if (metadata->fd != OBJDUMP_ERR)
    close(metadata->fd);
  return (OBJDUMP_OK);
}

int	main(int ac, char **av)
{
  int		i;
  t_metadata	metadata;

  metadata.return_value = OBJDUMP_OK;
  if (ac == 1)
    if (my_objdump(&metadata, "a.out") == OBJDUMP_ERR)
      return (OBJDUMP_ERR);
  for (i = 1; i < ac; i++)
    if (my_objdump(&metadata, av[i]) == OBJDUMP_ERR)
      metadata.return_value = OBJDUMP_ERR;
  return (metadata.return_value);
}
