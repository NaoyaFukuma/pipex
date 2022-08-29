/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:15:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/08/29 15:44:00 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_free(t_info *info)
{
	int	i;

	i = 0;
	while (info->cmd_args[i])
	{
		free(info->cmd_args[i]);
		i++;
	}
	free(info->cmd_args);
	free(info->cmd);
}

void	parent_free(t_info *info)
{
	int	i;

	i = 0;
	close(info->infile);
	close(info->outfile);
	while (info->cmd_paths[i])
	{
		free(info->cmd_paths[i]);
		i++;
	}
	free(info->cmd_paths);
}

void	close_parent_pipes(t_info *info)
{
	close(info->pipe_tube[0]);
	close(info->pipe_tube[1]);
}

char	*get_cmd(char **paths, char *argv_cmd)
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

void	cmd1_child(t_info info, char *argv[], char *envp[])
{
	dup2(info.pipe_tube[WRITE_FD], STDOUT);
	close(info.pipe_tube[READ_FD]);
	dup2(info.infile, STDIN);
	info.cmd_args = ft_split(argv[2], ' ');
	info.cmd = get_cmd(info.cmd_paths, info.cmd_args[0]);
	if (!info.cmd)
	{
		child_free(&info);
		exit(1);
	}
	execve(info.cmd, info.cmd_args, envp);
}

void	cmd2_child(t_info info, char *argv[], char *envp[])
{
	dup2(info.pipe_tube[READ_FD], STDIN);
	close(info.pipe_tube[WRITE_FD]);
	dup2(info.outfile, STDOUT);
	info.cmd_args = ft_split(argv[3], ' ');
	info.cmd = get_cmd(info.cmd_paths, info.cmd_args[0]);
	if (!info.cmd)
	{
		child_free(&info);
		exit(1);
	}
	execve(info.cmd, info.cmd_args, envp);
}

char	*find_env_in_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info info;

	if (argc != 5)
		return (1);
	info.infile = open(argv[1], O_RDONLY);
	if (info.infile < 0)
		return (1);
	info.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (info.outfile < 0)
		return (1);
	if (pipe(info.pipe_tube) < 0)
		return (1);
	info.paths = find_env_in_path(envp);
	info.cmd_paths = ft_split(info.paths, ':');
	info.pid1 = fork();
	if (info.pid1 == 0)
		cmd1_child(info, argv, envp);
	info.pid2 = fork();
	if (info.pid2 == 0)
		cmd2_child(info, argv, envp);
	close_parent_pipes(&info);
	waitpid(info.pid1, NULL, 0);
	waitpid(info.pid2, NULL, 0);
	close(info.infile);
	close(info.outfile);
	parent_free(&info);
	return (0);
}
