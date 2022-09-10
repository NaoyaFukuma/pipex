/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:45:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 00:48:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	util_close_all_fd(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->pipe_count)
		close(info->pipe_fd[i]);
	close(info->infile_fd);
	close(info->outfile_fd);
}

void	util_perror_exit(char *error_message)
{
	perror(error_message);
	exit(1);
}
