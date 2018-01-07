##
## Makefile for  in /home/hazer/Documents/tek2/Unix_Memoire/PSU_2016_nmobjdump
## 
## Made by hazer
## Login   <david.munoz@epitech.eu>
## 
## Started on  Mon Feb 13 12:03:50 2017 hazer
## Last update Mon Feb 13 12:17:03 2017 hazer
##

NM	= my_nm

OBJDUMP	= my_objdump

NM_DIR	= nm

OBJ_DIR	= objdump

RM      = rm -f

all:	objdump nm

$(NM):
	@(cd $(NM_DIR) && $(MAKE) && cp $(NM) ..)

$(OBJDUMP):
	@(cd $(OBJ_DIR) && $(MAKE) && cp $(OBJDUMP) ..)

nm:	$(NM)

objdump: $(OBJDUMP)

clean:
	@(cd $(NM_DIR) && ($(MAKE) clean))
	@(cd $(OBJ_DIR) && ($(MAKE) clean))

fclean:
	@$(RM) $(NM)
	@$(RM) $(OBJDUMP)
	@cd $(NM_DIR) && ($(MAKE) fclean)
	@cd $(OBJ_DIR) && ($(MAKE) fclean)

re: fclean all

.PHONY: all clean fclean re
