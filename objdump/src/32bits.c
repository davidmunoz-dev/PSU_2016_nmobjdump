/*
** 64bits.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:57:24 2017 hazer
** Last update Tue Feb 21 14:48:59 2017 hazer
*/

#include "objdump.h"

void	format32(t_data32 *data)
{
  if (data->elf->e_ident[EI_CLASS] == ELFCLASS32)
    printf("%s:	file format elf64-x86-64\n", data->file);
  else
    printf("%s:	file format elf32-i386\n", data->file);
}

void	objdump32bit(t_data32 *data)
{
  int	i;

  for (i = 0; i < data->elf->e_shnum; i++)
    if ((void *)(data->shdr + i) > (void*)(data->end))
      cerr_exit("objdump: The file is truncated\n", OBJDUMP_ERR);

  write(1, "\n", 1);
  format32(data);
  print_header32(data);
  write(1, "\n", 1);

  for (i = 0; i < data->elf->e_shnum; i++)
    if (good_type32(data, i) && data->shdr[i].sh_size != 0)
      print_compartment32(data, i);
}

int	do32bits(t_metadata *metadata)
{
  metadata->system = BIT32;

  if (metadata->data32.elf->e_ident[EI_MAG0] != ELFMAG0
      || metadata->data32.elf->e_ident[EI_MAG1] != ELFMAG1
      || metadata->data32.elf->e_ident[EI_MAG2] != ELFMAG2
      || metadata->data32.elf->e_ident[EI_MAG3] != ELFMAG3
      || metadata->data32.elf->e_ident[EI_CLASS] != ELFCLASS32)
    return (cerr_ret("objdump: File format is not recognized\n", OBJDUMP_ERR));
  if ((metadata->data32.shdr = (Elf32_Shdr *)(metadata->data32.data +
					      metadata->data32.elf->e_shoff)) == NULL)
    return (cerr_ret("objdump: Invalid pointer\n", OBJDUMP_ERR));
  if ((void*)metadata->data32.shdr >= (void*)metadata->data32.end)
    return (cerr_ret("objdump: The file is truncated\n", OBJDUMP_ERR));
  if ((metadata->data32.strtab = (char*)(metadata->data32.data +
					 metadata->data32.shdr[metadata->data32.elf->e_shstrndx].sh_offset))==NULL)
    return (cerr_ret("objdump: Invalid pointer\n", OBJDUMP_ERR));
  if ((void *)metadata->data32.strtab >= (void *)metadata->data32.end)
    return (cerr_ret("objdump: The file is truncated", OBJDUMP_ERR));
  if (metadata->data32.strtab && metadata->data32.shdr && metadata->data32.elf)
    return (OBJDUMP_OK);
  return (OBJDUMP_ERR);
}
