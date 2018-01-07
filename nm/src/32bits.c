/*
** 32bits.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <hazer@epitech.net>
**
** Started on  Tue Feb 21 15:55:12 2017 hazer
** Last update Tue Feb 21 15:55:39 2017 hazer
*/

#include "nm.h"

void	symbole32(t_data32 *data)
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
	  data->size_symtab = data->shdr[i].sh_size / sizeof(Elf32_Sym);
	  data->sym = (Elf32_Sym*)(data->data + data->shdr[i].sh_offset);
	}
    }
  if (data->sym == NULL
      || data->true_str == NULL
      || data->size_symtab == 0)
    cerr_exit("nm: No symbole in the file\n", NM_ERR);
}

void	nm32bit(t_data32 *data)
{
  int                   i;
  Elf32_Sym             *tmp;
  t_elem32             *new;

  symbole32(data);
  add_elem32(data);
  if ((new = malloc(data->size_symtab * sizeof(t_elem32))) == NULL)
    return (cerr_exit("nm: Malloc failed", NM_ERR));
  new = sort_data32(data->elem, new, 0, data->size_symtab);
  if (data->elem)
    free(data->elem);
  data->elem = new;
  for (i = 0; i < data->size_symtab; i++)
    {
      tmp = data->elem[i].elem;
      if (tmp)
	print_info32(data, tmp, i);
    }
  if (data->elem)
    free(data->elem);
}

int	do32bits(t_metadata *metadata)
{
  metadata->system = BIT32;

  if (metadata->data32.elf->e_ident[EI_MAG0] != ELFMAG0
      || metadata->data32.elf->e_ident[EI_MAG1] != ELFMAG1
      || metadata->data32.elf->e_ident[EI_MAG2] != ELFMAG2
      || metadata->data32.elf->e_ident[EI_MAG3] != ELFMAG3
      || metadata->data32.elf->e_ident[EI_CLASS] != ELFCLASS32)
    return (cerr_ret("nm: File format not recognized\n", NM_ERR));
  if ((metadata->data32.shdr = (Elf32_Shdr *)(metadata->data32.data +
					      metadata->data32.elf->e_shoff)) == NULL)
    return (cerr_ret("nm: Invalid pointer\n", NM_ERR));
  if ((void*)metadata->data32.shdr >= (void*)metadata->data32.end)
    return (cerr_ret("nm: The file is truncated\n", NM_ERR));
  if ((metadata->data32.str = (char*)(metadata->data32.data +
					 metadata->data32.shdr[metadata->data32.elf->e_shstrndx].sh_offset))==NULL)
    return (cerr_ret("nm: Invalid pointer\n", NM_ERR));
  if ((void *)metadata->data32.str >= (void *)metadata->data32.end)
    return (cerr_ret("nm: The file is truncated", NM_ERR));
  if (metadata->data32.str && metadata->data32.shdr && metadata->data32.elf)
    return (NM_OK);
  return (NM_ERR);
}
