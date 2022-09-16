/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:45:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/16 13:51:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	util_close_all_fd(t_info *info)
{
	int	i;

	i = -1;
	while (++i < 2)
		close(info->pipe_fd[i]);
	close(info->infile_fd);
	close(info->outfile_fd);
}

void	util_perror_exit(char *error_message)
{
	ft_putstr_fd("\x1b[31m", STDERR_FILENO);
	perror(error_message);
	ft_putstr_fd("\x1b[39m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
