# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 00:02:32 by nfukuma           #+#    #+#              #
#    Updated: 2022/08/29 15:20:21 by nfukuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#for set up
NAME		=	pipex
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

#for heder file and path
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

#for mandatory file and path
SRCNAMES_M	=	main.c
SRCDIR_M	=	mandatory/
SRCS_M		=	$(addprefix $(SRCDIR_M), $(SRCNAMES_M))
OBJS_M		=	$(SRCS_M:%.c=%.o)

#for bonus file and path
SRCNAMES_B	=
SRCDIR_B	=	bonus/
SRCS_B		=	$(addprefix $(SRCDIR_B), $(SRCNAMES_B))
OBJS_B		=	$(SRCS_B:%.c=%.o)

#.a library path
LIBDIR		=	./libft
GNLDIR		=	./libgnl

#target rule
all	:	$(NAME)

$(NAME)	:	$(OBJS_M)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -I../includes -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl -o $@ $^

bonus	:	$(OBJS_B)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -I../includes -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl -o $(NAME) $(OBJS_B)

clean	:
	$(RM) $(OBJS_M)
	$(RM) $(OBJS_B)
	make -C $(LIBDIR) clean;
	make -C $(GNLDIR) clean;

fclean	:	clean
	make -C $(LIBDIR) fclean;
	make -C $(GNLDIR) fclean;
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all bonus clean fclean re
