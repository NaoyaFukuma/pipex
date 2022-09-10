/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:46:51 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 01:39:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	set_child_fd(t_info *info, int i);
static char	*get_full_path_cmd(char *cmd, char **envp);

void	exe_child(int i, t_info *info, char **argv, char **envp)
{
	pid_t	pid;
	char	*child_execmd;
	char	**child_argv;

	pid = fork();
	if (pid == -1)
		util_perror_exit("Error: fork");
	if (!pid)
	{
		if (set_child_fd(info, i) == -1)
			util_perror_exit("Error: dup2");
		util_close_all_fd(info);
		child_argv = ft_split(argv[2 + i], ' ');
		if (!child_argv)
			util_perror_exit("Error: split");
		child_execmd = get_full_path_cmd(child_argv[0], envp);
		if (!child_execmd)
			util_perror_exit("Error: command not found");
		execve(child_execmd, child_argv, envp);
		util_perror_exit(child_execmd);
	}
}

static int	set_child_fd(t_info *info, int i)
{
	if (i == 0)
	{
		if (dup2(info->infile_fd, STDIN) == -1)
			return (-1);
		if (dup2(info->pipe_fd[1], STDOUT) == -1)
			return (-1);
	}
	else
	{
		if (dup2(info->pipe_fd[0], STDIN) == -1)
			return (-1);
		if (dup2(info->outfile_fd, STDOUT) == -1)
			return (-1);
	}
	return (0);
}

static char	*get_full_path_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*full_path_cmd;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	paths = ft_split(&envp[0][5], ':');
	if (!paths)
		util_perror_exit("Error: ft_split");
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (tmp == NULL)
			util_perror_exit("strjoin error");
		full_path_cmd = ft_strjoin(tmp, cmd);
		if (full_path_cmd == NULL)
			util_perror_exit("strjoin error");
		free(tmp);
		if (access(full_path_cmd, 0) == 0)
			return (full_path_cmd);
		free(full_path_cmd);
		paths++;
	}
	return (NULL);
}
