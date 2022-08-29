/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libget_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:51:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/08/27 00:07:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGET_NEXT_LINE_H
# define LIBGET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

typedef struct s_fd_info
{
	int					fd;
	char				*text;
	size_t				text_len;
	int					fin_flag;
	struct s_fd_info	*previous;
	struct s_fd_info	*next;
}						t_fd_info;

// in .c
char					*get_next_line(int fd);
t_fd_info				*ft_newnode(int fd, t_fd_info *prvious);
char					*ft_strchar(char *str, char c);
char					*ft_split_and_store_text(char *str, size_t strlen,
							t_fd_info *strage_p);
t_fd_info				*ft_set_pointer(t_fd_info **static_p,
							t_fd_info **strage_p, int fd);

// in utils.c
char					*ft_strcat_and_free(char **s1, char **s2, size_t len);
char					*ft_delete_one_strage(t_fd_info **static_p,
							t_fd_info **strage_p);
char					*ft_push_end_line(t_fd_info **strage_p);
char					*ft_read_file_push_line(t_fd_info **strage_p,
							t_fd_info **static_p);
char					*ft_parse_readsize(ssize_t readsize, char **buf,
							t_fd_info **strage_p, t_fd_info **static_p);

#endif
