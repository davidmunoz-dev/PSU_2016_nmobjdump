/*
** nm.h for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump/nm/inc
**
** Made by hazer
** Login   <david.munoz@epitech.eu>
**
** Started on  Tue Feb 14 17:09:36 2017 hazer
** Last update Tue Feb 21 14:48:41 2017 hazer
*/

#ifndef _OBJDUMP_H_
# define _OBJDUMP_H_

#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <string.h>

#define OBJDUMP_OK	0
#define	OBJDUMP_ERR	-1

#define	BIT32	32
#define BIT64	64

typedef struct	s_data64
{
  void		*data;
  void		*end;
  char		*strtab;
  char		*file;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
}		t_data64;

typedef struct	s_data32
{
  void		*data;
  void		*end;
  char		*strtab;
  char		*file;
  Elf32_Ehdr	*elf;
  Elf32_Shdr	*shdr;
}		t_data32;

typedef struct	s_metadata
{
  int	fd;
  int	system;
  int	return_value;
  t_data32	data32;
  t_data64	data64;
}		t_metadata;

typedef	struct	s_type
{
  int	type;
  char	*type_name;
}		t_type;

/*	32bits.c	*/
void    objdump32bit(t_data32 *data);
int     do32bits(t_metadata *data);
void	format32(t_data32 *data);

/*	32bits_fc.c	*/
int     good_type32(t_data32 *data, int i);
void	print_compartment32(t_data32 *data, int shnum);
void	print_header32(t_data32 *data);

/*	64bits.c	*/
void    objdump64bit(t_data64 *data);
int     do64bits(t_metadata *data);
void	format64(t_data64 *data);

/*	64bit_fc.c	*/
int     good_type64(t_data64 *data, int i);
void	print_compartment64(t_data64 *data, int shnum);
void	print_header64(t_data64 *data);

/*	main.c		*/

/*	utils.c		*/
void    print_sub(char str[16], unsigned int *hex, char ok, int end, int i);

char    is_printable(char c);
int	filesize(int fd);

/*	header.c	*/
char	*architecture(int type);

/*	error.c		*/
int	err_opening(char *file, int err);
int	cerr_ret(char *str, int err);
void	cerr_exit(char *str, int err);

#endif	/* !_OBJDUMP_H_ */
