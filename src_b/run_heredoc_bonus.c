/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:21:42 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/11 00:52:27 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	run_heredoc(char *limitter, t_info *info)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		util_perror_exit("Error: open");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		buf = get_next_line(0);
		if (!ft_strncmp(limitter, buf, ft_strlen(limitter)))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	info->infile_fd = open(".heredoc_tmp", O_RDONLY);
	if (info->infile_fd < 0)
	{
		unlink(".heredoc_tmp");
		util_perror_exit("Error: open");
	}
}
