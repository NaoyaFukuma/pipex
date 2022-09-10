/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 23:15:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 02:04:35 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	validate_arg_and_set_info(int argc, char **argv, t_info *info);
static void	open_infile_fd(char *infile_path, t_info *info);
static void	open_outfile_fd(char *outfile_path, t_info *info);
static void	open_pipe_fd(t_info *info);

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		i;

	validate_arg_and_set_info(argc, argv, &info);
	i = -1;
	while (++i < 2)
		exe_child(i, &info, argv, envp);
	util_close_all_fd(&info);
	i = -1;
	while (++i < 2)
		if (waitpid(-1, NULL, 0) == -1)
			util_perror_exit("Error: wait");
	return (0);
}

static void	validate_arg_and_set_info(int argc, char **argv, t_info *info)
{
	if (argc != 5)
		util_perror_exit("Error: invalid number of arguments");
	open_infile_fd(argv[1], info);
	open_outfile_fd(argv[4], info);
	open_pipe_fd(info);
}

static void	open_pipe_fd(t_info *info)
{
	info->pipe_fd = malloc(sizeof(int) * 2);
	if (!info->pipe_fd)
		util_perror_exit("Error: malloc");
	if (pipe(info->pipe_fd) < 0)
		util_perror_exit("Error: pipe");
}

static void	open_infile_fd(char *infile_path, t_info *info)
{
	info->infile_fd = open(infile_path, O_RDONLY);
	if (info->infile_fd < 0)
		util_perror_exit("Error: open");
}

static void	open_outfile_fd(char *outfile_path, t_info *info)
{
	info->outfile_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC,
			0000644);
	if (info->outfile_fd < 0)
		util_perror_exit("Error: open");
}
