/*
** utils.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:49:18 2017 hazer
** Last update Tue Feb 21 21:43:49 2017 hazer
*/

#include "objdump.h"
#include "flags.h"

int		good_type64(t_data64 *data, int i)
{
  int	data_alloc;
  int	data_write;

  data_write = data->shdr[i].sh_flags & SHF_WRITE;
  data_alloc = data->shdr[i].sh_flags & SHF_ALLOC;
  if (data->shdr[i].sh_type == SHT_NOBITS)
    return (OBJDUMP_ERR);
  if (data->shdr[i].sh_type == SHT_PROGBITS
      || data->shdr[i].sh_type == SHT_NOTE
      || data_alloc == SHF_ALLOC || data_write == SHF_WRITE)
    return (OBJDUMP_ERR);
  return (OBJDUMP_OK);
}

void		print_compartment64(t_data64 *data, int shnum)
{
  char		str[16];
  unsigned int	hex;
  unsigned int	i;
  unsigned char	tmp;

  hex = (unsigned int)(data->shdr[shnum].sh_addr);
  str[0] = 0;
  printf("Contents of section %s:\n",
	 &(data->strtab[data->shdr[shnum].sh_name]));
  for (i = 0; i < data->shdr[shnum].sh_size; i++)
    {
      tmp = *(char*)(data->data + data->shdr[shnum].sh_offset + i);
      if (i % 16 == 0)
	print_sub(str, &hex, 1, 16, i);
      else if (i % 4 == 0)
	printf(" ");
      printf("%02x", tmp);
      str[i % 16] = tmp;
    }
  if (i % 16 != 0)
    print_sub(str, &hex, 0, i % 16, i);
  if (i % 16 == 0)
    print_sub(str, &hex, 0, 16, i);
}

void	print_header64(t_data64 *data)
{
  int   ftypes[ET_NUM];
  char  *types[ET_NUM];

  types[ET_NONE] = "";
  ftypes[ET_NONE] = 0x0;
  types[ET_REL] = "HAS_RELOC, HAS_SYMS";
  ftypes[ET_REL] = 0x11;
  types[ET_EXEC] = "EXEC_P, HAS_SYMS, D_PAGED";
  ftypes[ET_EXEC] = 0x112;
  types[ET_DYN] = "HAS_SYMS, DYNAMIC, D_PAGED";
  ftypes[ET_DYN] = 0x150;
  types[ET_CORE] = "";
  ftypes[ET_CORE] = 0x0;
  if (data->elf->e_type < ET_NUM)
    {
      printf("architecture: i386:x86-64, flags 0x%08x:\n", ftypes[data->elf->e_type]);
      printf("%s\n", types[data->elf->e_type]);
      printf("start address 0x%016lx\n", data->elf->e_entry);
    }
}
