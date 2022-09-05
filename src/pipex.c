/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:15:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/02 12:59:14 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	set_info(int argc, char *argv[], char *envp[], t_info *info);
static void	get_infile(char **argv, t_info *info);
static void	get_outfile(char *argv, t_info *info);
static void	get_pipe_tube(t_info *info);

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	if (argc != 5)
		return (1);
	set_info(argc, argv, envp, &info);
	get_pipe_tube(&info);
	exe_child(argv, envp, &info);
	close_all_pipes(&info);
	if (waitpid(-1, info.status_ptr, 0) == -1)
		exit(1);
	if (info.status_ptr)
		exit(1);
	parent_free(&info);
	return (0);
}

static void	set_info(int argc, char *argv[], char *envp[], t_info *info)
{
	get_infile(argv, info);
	get_outfile(argv[argc - 1], info);
	info->cmd_count = argc - 3;
	info->pipe_count = (info->cmd_count - 1) * 2;
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	info->cmd_paths = ft_split(&envp[0][5], ':');
	if (!info->cmd_paths)
		exit(1);
	info->status_ptr = malloc(sizeof(int));
	if (!info->status_ptr)
		exit(1);
	*(info->status_ptr) = 0;
}

static void	get_pipe_tube(t_info *info)
{
	int	i;

	info->pipe_tube = malloc(sizeof(int) * info->pipe_count);
	if (!info->pipe_tube)
		exit(1);
	i = 0;
	while (i < info->cmd_count - 1)
	{
		if (pipe(&(info->pipe_tube[2 * i])) < 0)
			exit(1);
		i++;
	}
}

static void	get_infile(char **argv, t_info *info)
{
	info->infile = open(argv[1], O_RDONLY);
	if (info->infile < 0)
		exit(1);
}

static void	get_outfile(char *argv, t_info *info)
{
	info->outfile = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (info->outfile < 0)
		exit(1);
}
