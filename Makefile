# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 00:02:32 by nfukuma           #+#    #+#              #
#    Updated: 2022/09/01 01:30:18 by nfukuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#for set up
NAME		=	pipex
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf


#for sorc file and path mondatory or bonus
ifeq			($(WITH_BONUS), 1)
SRCNAMES_B	=	child_bonus.c free_or_close_utils_bonus.c heredoc_bonus.c pipex_bonus.c
SRCDIR		=	src/
SRCS_B		=	$(addprefix $(SRCDIR), $(SRCNAMES_B))
OBJS		=	$(SRCS_B:%.c=%.o)
else
SRCNAMES	=	child.c free_or_close_utils.c pipex.c
SRCDIR		=	src/
SRCS		=	$(addprefix $(SRCDIR), $(SRCNAMES))
OBJS		=	$(SRCS:%.c=%.o)
endif



#.a library path
LIBDIR		=	./libft
GNLDIR		=	./libgnl

#target rule
all	:	$(NAME)

$(NAME)	:	$(OBJS)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl -o $@ $^

bonus	:
	make WITH_BONUS=1

clean	:
	$(RM) ./src/child_bonus.o ./src/free_or_close_utils_bonus.o ./src/heredoc_bonus.o ./src/pipex_bonus.o ./src/child.o ./src/free_or_close_utils.o ./src/pipex.o
	make -C $(LIBDIR) clean;
	make -C $(GNLDIR) clean;

fclean	:	clean
	make -C $(LIBDIR) fclean;
	make -C $(GNLDIR) fclean;
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re bonus
