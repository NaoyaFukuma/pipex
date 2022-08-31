/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_close_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:45:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/01 00:25:11 by nfukuma          ###   ########.fr       */
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
	free(info->pipe_tube);
}

void	close_all_pipes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->pipe_count)
		close(info->pipe_tube[i]);
}
