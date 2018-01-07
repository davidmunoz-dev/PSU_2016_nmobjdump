/*
** utils.c for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/src
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Wed Feb 15 14:49:18 2017 hazer
** Last update Tue Feb 21 16:00:09 2017 hazer
*/

#include "nm.h"

t_elem32		*sort_data32(t_elem32 *base, t_elem32 *new,
				     int pos, int size)
{
  int                   i;
  t_elem32             *tmp;

  tmp = &base[0];
  for (i = 0; i < size; i++)
    if (base[i].elem && *(base[i].name) && base[i].elem != NULL)
      if (get_greater(tmp->name, base[i].name) == 2)
	tmp = &base[i];
  if (tmp->elem && *tmp->name && tmp->elem->st_info != STT_FILE)
    {
      new[pos].name = tmp->name;
      new[pos].elem = tmp->elem;
      new[pos].pos = pos;
    }
  else if (*tmp->name == 0)
    return (new);
  else
    new[pos].elem = NULL;
  tmp->elem = NULL;
  pos++;
  if ((pos + 1) < size)
    sort_data32(base, new, pos, size);
  return (new);
}

void	print_info32(t_data32 *data, Elf32_Sym *tmp, int i)
{
  if (tmp->st_value)
    {
      printf("%016u %c %s\n",
	     tmp->st_value,
	     get_type(data->shdr[tmp->st_shndx].sh_type,
			  data->shdr[tmp->st_shndx].sh_flags,
			  tmp->st_info,
			  tmp->st_value),
	     data->elem[i].name);
    }
  else
    {
      printf("                 %c %s\n",
	     get_type(data->shdr[tmp->st_shndx].sh_type,
			  data->shdr[tmp->st_shndx].sh_flags,
			  tmp->st_info,
			  tmp->st_value),
	     data->elem[i].name);
    }
}

void	add_elem32(t_data32 *data)
{
  t_elem32	*elem;
  int		i;

  if ((elem = malloc(data->size_symtab * sizeof(t_elem32))) == NULL)
    cerr_exit("nm: Malloc failed\n", NM_ERR);
  for (i = 0; i < data->size_symtab; i++)
    {
      elem[i].name = (char*)(data->true_str + data->sym[i].st_name);
      elem[i].elem = data->sym + i;
      elem[i].pos = i;
    }
  data->elem = elem;
}
