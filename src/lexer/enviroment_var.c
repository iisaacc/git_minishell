/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:14:38 by isporras          #+#    #+#             */
/*   Updated: 2024/01/17 13:51:22 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_extend_var(char **lexer)
{
	int		i;
	int		j;
	char	*var;
	char	*value;

	i = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if (lexer[i][j] == '$')
			{
				var = ft_substr(lexer[i], j + 1, ft_strlen(lexer[i]) - j);
				value = getenv(var);
				if (value)
				{
					free(lexer[i]);
					lexer[i] = ft_strdup(value);
				}
				free(var);
			}
			j++;
		}
		i++;
	}
}
