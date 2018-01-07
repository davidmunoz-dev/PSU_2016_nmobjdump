/*
** nm.h for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/inc
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Tue Feb 14 17:09:36 2017 hazer
** Last update Tue Feb 21 16:01:21 2017 hazer
*/

#ifndef _NM_H_
# define _NM_H_

#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <string.h>

#define NM_OK	0
#define	NM_ERR	-1

#define	BIT32	32
#define BIT64	64

typedef struct	s_elem64
{
  Elf64_Sym	*elem;
  char		*name;
  int		pos;
}		t_elem64;

typedef struct	s_data64
{
  Elf64_Sym	*sym;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
  char		*str;
  char		*file;
  char		*true_str;
  int		size_symtab;
  void		*data;
  void		*end;
  t_elem64	*elem;
}		t_data64;

typedef struct	s_elem32
{
  Elf32_Sym	*elem;
  char		*name;
  int		pos;
}		t_elem32;

typedef struct	s_data32
{
  Elf32_Sym	*sym;
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*shdr;
  char		*str;
  char		*file;
  char		*true_str;
  int		size_symtab;
  void		*data;
  void		*end;
  t_elem32	*elem;
}		t_data32;

typedef struct	s_metadata
{
  int	fd;
  int	system;
  int	return_value;
  t_data32	data32;
  t_data64	data64;
}		t_metadata;

/*	32bits.c	*/
int     do32bits(t_metadata *metadata);

/*	32bits_fc.c	*/
t_elem32	*sort_data32(t_elem32 *base, t_elem32 *new, int pos, int size);
void		add_elem32(t_data32 *data);
void		print_info32(t_data32 *data, Elf32_Sym *tmp, int i);

/*	64bits.c	*/
int     do64bits(t_metadata *data);

/*	64bit_fc.c	*/
t_elem64	*sort_data64(t_elem64 *base, t_elem64 *new, int pos, int size);
void		add_elem64(t_data64 *data);
void		print_info64(t_data64 *data, Elf64_Sym *tmp, int i);


/*	main.c		*/
void	nm64bit(t_data64 *data);
void	nm32bit(t_data32 *data);

/*	utils.c		*/
int		filesize(int fd);
char            get_type(int type, int flags, int info, int value);
int		get_greater(char *str1, char *str2);

/*	error.c		*/
int	err_opening(char *file, int err);
int	cerr_ret(char *str, int err);
void	cerr_exit(char *str, int err);

#endif	/* !_NM_H_ */
