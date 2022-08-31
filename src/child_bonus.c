/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:46:51 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/01 00:04:09 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	sub_dup2(int in_pipe, int out_pipe);
static char	*get_cmd(char **paths, char *argv_cmd);

void	exe_child(char *argv[], char *envp[], t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->cmd_count)
	{
		info->pid = fork();
		if (!info->pid)
		{
			if (i == 0)
				sub_dup2(info->infile, info->pipe_tube[1]);
			else if (i == info->cmd_count - 1)
				sub_dup2(info->pipe_tube[2 * i - 2], info->outfile);
			else
				sub_dup2(info->pipe_tube[2 * i - 2], info->pipe_tube[2 * i
						+ 1]);
			close_all_pipes(info);
			info->cmd_args = ft_split(argv[2 + info->heredoc_flag + i], ' ');
			info->cmd = get_cmd(info->cmd_paths, info->cmd_args[0]);
			if (!info->cmd)
				child_free(info);
			execve(info->cmd, info->cmd_args, envp);
		}
	}
}

static void	sub_dup2(int in_pipe, int out_pipe)
{
	dup2(in_pipe, STDIN);
	dup2(out_pipe, STDOUT);
}

static char	*get_cmd(char **paths, char *argv_cmd)
{
	char	*tmp;
	char	*cmd;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd = ft_strjoin(tmp, argv_cmd);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		paths++;
	}
	return (NULL);
}