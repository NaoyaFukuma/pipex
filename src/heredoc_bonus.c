/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:21:42 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/01 00:04:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	check_heredoc(char *argv1, t_info *info)
{
	if (!ft_strncmp("here_doc", argv1, 9))
	{
		info->heredoc_flag = 1;
		return (6);
	}
	else
	{
		info->heredoc_flag = 0;
		return (5);
	}
}

void	run_heredoc(char *limitter, t_info *info)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		exit(1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!ft_strncmp(limitter, buf, ft_strlen(limitter)))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	info->infile = open(".heredoc_tmp", O_RDONLY);
	if (info->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}
