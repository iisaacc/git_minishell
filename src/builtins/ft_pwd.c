/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:31:16 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/07 11:31:29 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(int fd)
{
	char buffer[1024];
	char *pwd;
	
	pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	while (*pwd)
	{
		write(fd, &(*pwd), 1);
		pwd++;
	}
	write(fd, "\n", 1);
	free(pwd);
}