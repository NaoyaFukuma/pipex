# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 00:02:32 by nfukuma           #+#    #+#              #
#    Updated: 2022/09/11 01:59:18 by nfukuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#for set up
NAME		=	pipex
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf


#for sorc file and path mondatory or bonus
SRCNAMES_B	=	main_bonus.c \
				exe_child_bonus.c \
				run_heredoc_bonus.c \
				utils_bonus.c
SRCDIR_B		=	src_b/
SRCS_B		=	$(addprefix $(SRCDIR_B), $(SRCNAMES_B))
OBJS_B		=	$(SRCS_B:%.c=%.o)

SRCNAMES	=	main.c \
				exe_child.c \
				utils.c
SRCDIR		=	src/
SRCS		=	$(addprefix $(SRCDIR), $(SRCNAMES))
OBJS		=	$(SRCS:%.c=%.o)

#.a library path
LIBDIR		=	./libft
GNLDIR		=	./libgnl

#target rule
all	:	$(NAME)

ifeq			($(WITH_BONUS), 1)
$(NAME)	:	$(OBJS_B)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl -o $@ $^
else
$(NAME)	:	$(OBJS)
	make -C $(LIBDIR)
	make -C $(GNLDIR)
	$(CC) $(CFLAGS) -L $(LIBDIR) -L $(GNLDIR) -lft -lgnl -o $@ $^
endif

bonus	:
	make WITH_BONUS=1

clean	:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)
	make -C $(LIBDIR) clean;
	make -C $(GNLDIR) clean;

fclean	:	clean
	make -C $(LIBDIR) fclean;
	make -C $(GNLDIR) fclean;
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re bonus
