/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:10:58 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 01:56:54 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Examples
// ----mondatory----
// 1) argc=5 argv[0]  [1]    [2]     [3]     [4]       [5]
//       $> ./pipex infile "ls -l" "wc -l" outfile     NULL
// Should behave like: < infile ls -l | wc -l > outfile
//
// 2)
// $> ./pipex infile "grep a1" "wc -w " outfile
// Should behave like: < infile grep a1 | wc -w > outfile
// -----------------

// ----bonus----
// 1) Handle multiple pipes.
// This:
//          $> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// Should behave like:
//          < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
// 2) Support « and » when the first parameter is "here_doc". This:
//          $> ./pipex here_doc LIMITER cmd cmd1 file
// Should behave like:
//          cmd << LIMITER | cmd1 >> file
// -------------

/* for write, read, close, access, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

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
# include "../libft/libft.h"
# include "../libgnl/libget_next_line.h"

/* fd management */
# define READ_FD 0
# define WRITE_FD 1
# define STDIN 0
# define STDOUT 1

typedef struct s_info
{
	int	infile_fd;
	int	outfile_fd;
	int	*pipe_fd;
}		t_info;

/* in utils.c */
void	util_close_all_fd(t_info *info);
void	util_perror_exit(char *error_message);

/* in exe_child.c */
void	exe_child(int i, t_info *info, char **argv, char **envp);

#endif
