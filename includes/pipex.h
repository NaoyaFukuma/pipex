/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:10:58 by nfukuma           #+#    #+#             */
/*   Updated: 2022/08/29 14:45:26 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

// Examples
// 1) argc=5 argv[0]  [1]    [2]     [3]     [4]       [5]
//       $> ./pipex infile "ls -l" "wc -l" outfile     NULL
// Should behave like: < infile ls -l | wc -l > outfile
//
// 2)
// $> ./pipex infile "grep a1" "wc -w " outfile
// Should behave like: < infile grep a1 | wc -w > outfile


/* for write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* for malloc, free, exit */
# include <stdlib.h>

/* for open, unlink */
# include <fcntl.h>

/* for waitpid, wait */
# include <sys/wait.h>

/* for strerror */
# include <string.h>

/* for perror */
# include <stdio.h>

/* for libft */
#include "../libft/libft.h"

# define READ_FD 0
# define WRITE_FD 1
# define STDIN 0
# define STDOUT 1

typedef struct s_info
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_info;


#endif
