/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:28:59 by isporras          #+#    #+#             */
/*   Updated: 2024/02/08 15:29:21 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_here_doc(t_mini *mini, char *eof)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, eof, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	mini->infile = fd[0];
}
