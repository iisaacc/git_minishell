/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:38:32 by isporras          #+#    #+#             */
/*   Updated: 2024/01/18 11:38:32 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_find_cmnd_path(char **envp, char *cmnd)
{
	int		i;
	char	**path_split;
	char	*fullpath;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_split = ft_split(&envp[i][5], ':');
			i = 0;
			while (path_split[i])
			{
				fullpath = ft_strjoin(path_split[i], "/");
				fullpath = ft_strjoin(fullpath, cmnd);
				if (access(fullpath, F_OK) == 0)
					return (ft_free_2d(path_split), fullpath);
				ft_bzero(fullpath, ft_strlen(fullpth));
				i++;
			}
		}
		i++;
	}
	free(fullpath);
	ft_free_2d(path_split);
	return (NULL);
}