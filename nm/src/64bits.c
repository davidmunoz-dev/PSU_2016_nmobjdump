/*
** 64bits.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:57:24 2017 hazer
** Last update Tue Feb 21 15:48:06 2017 hazer
*/

#include "nm.h"

void	symbole64(t_data64 *data)
{
  int	i;

  data->sym = NULL;
  data->true_str = NULL;
  data->size_symtab = 0;
  for (i = 0; i < data->elf->e_shnum; i++)
    {
      if (data->shdr[i].sh_type == SHT_STRTAB
	  && (data->shdr[i].sh_flags | SHF_ALLOC) == SHF_ALLOC
	  && (data->data + data->shdr[i].sh_offset) != data->str)
	data->true_str = (char*)(data->data
				    + data->shdr[i].sh_offset);
      if (data->shdr[i].sh_type == SHT_SYMTAB)
	{
	  data->size_symtab = data->shdr[i].sh_size / sizeof(Elf64_Sym);
	  data->sym = (Elf64_Sym*)(data->data + data->shdr[i].sh_offset);
	}
    }
  if (data->sym == NULL
      || data->true_str == NULL
      || data->size_symtab == 0)
    cerr_exit("nm: No symbole in the file\n", NM_ERR);
}

void	nm64bit(t_data64 *data)
{
  int                   i;
  Elf64_Sym             *tmp;
  t_elem64             *new;

  symbole64(data);
  add_elem64(data);
  if ((new = malloc(data->size_symtab * sizeof(t_elem64))) == NULL)
    return (cerr_exit("nm: Malloc failed", NM_ERR));
  new = sort_data64(data->elem, new, 0, data->size_symtab);
  if (data->elem)
    free(data->elem);
  data->elem = new;
  for (i = 0; i < data->size_symtab; i++)
    {
      tmp = data->elem[i].elem;
      if (tmp)
	print_info64(data, tmp, i);
    }
  if (data->elem)
    free(data->elem);
}

int	do64bits(t_metadata *metadata)
{
  metadata->system = BIT64;

  if (metadata->data64.elf->e_ident[EI_MAG0] != ELFMAG0
      || metadata->data64.elf->e_ident[EI_MAG1] != ELFMAG1
      || metadata->data64.elf->e_ident[EI_MAG2] != ELFMAG2
      || metadata->data64.elf->e_ident[EI_MAG3] != ELFMAG3
      || metadata->data64.elf->e_ident[EI_CLASS] != ELFCLASS64)
    return (cerr_ret("nm: File format not recognized\n", NM_ERR));
  if ((metadata->data64.shdr = (Elf64_Shdr *)(metadata->data64.data +
					      metadata->data64.elf->e_shoff)) == NULL)
    return (cerr_ret("nm: Invalid pointer\n", NM_ERR));
  if ((void*)metadata->data64.shdr >= (void*)metadata->data64.end)
    return (cerr_ret("nm: The file is truncated\n", NM_ERR));
  if ((metadata->data64.str = (char*)(metadata->data64.data +
					 metadata->data64.shdr[metadata->data64.elf->e_shstrndx].sh_offset))==NULL)
    return (cerr_ret("nm: Invalid pointer\n", NM_ERR));
  if ((void *)metadata->data64.str >= (void *)metadata->data64.end)
    return (cerr_ret("nm: The file is truncated", NM_ERR));
  if (metadata->data64.str && metadata->data64.shdr && metadata->data64.elf)
    return (NM_OK);
  return (NM_ERR);
}
