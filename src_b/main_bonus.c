/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:15:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 01:30:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	validate_arg_and_set_info(int argc, char **argv, t_info *info);
static void	open_infile_fd(char **argv, t_info *info);
static void	open_outfile_fd(char *outfile_path, t_info *info);
static void	open_pipe_fd(t_info *info);

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		i;

	validate_arg_and_set_info(argc, argv, &info);
	i = -1;
	while (++i < info.cmd_count)
		exe_child(i, &info, argv, envp);
	util_close_all_fd(&info);
	i = -1;
	while (++i < info.cmd_count)
		if (waitpid(-1, NULL, 0) == -1)
			util_perror_exit("Error: wait");
	return (0);
}

static void	validate_arg_and_set_info(int argc, char **argv, t_info *info)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		info->heredoc_flag = 1;
	else
		info->heredoc_flag = 0;
	if (info->heredoc_flag == 1 && argc != 6)
		util_perror_exit("Error: invalid number of arguments");
	if (info->heredoc_flag == 0 && argc < 6)
		util_perror_exit("Error: invalid number of arguments");
	info->cmd_count = argc - 3 - info->heredoc_flag;
	info->pipe_count = (info->cmd_count - 1) * 2;
	open_infile_fd(argv, info);
	open_outfile_fd(argv[argc - 1], info);
	open_pipe_fd(info);
}

static void	open_pipe_fd(t_info *info)
{
	int	i;

	info->pipe_fd = malloc(sizeof(int) * info->pipe_count);
	if (!info->pipe_fd)
		util_perror_exit("Error: malloc");
	i = -1;
	while (++i < info->cmd_count - 1)
		if (pipe(&(info->pipe_fd[2 * i])) < 0)
			util_perror_exit("Error: pipe");
}

static void	open_infile_fd(char **argv, t_info *info)
{
	if (info->heredoc_flag)
		run_heredoc(argv[2], info);
	else
	{
		info->infile_fd = open(argv[1], O_RDONLY);
		if (info->infile_fd < 0)
			util_perror_exit("zsh: no such file or directory: non_exist_input");
	}
}

static void	open_outfile_fd(char *outfile_path, t_info *info)
{
	if (info->heredoc_flag)
		info->outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND,
				0000644);
	else
		info->outfile_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC,
				0000644);
	if (info->outfile_fd < 0)
		util_perror_exit("Error: open");
}
