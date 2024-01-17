/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:49 by isporras          #+#    #+#             */
/*   Updated: 2024/01/17 14:13:56 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_get_tokens(char **lexer)
{
	int		i;
	int		j;
	char	*token;
	char	**tmp;

	i = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if (lexer[i][j] == '>' || lexer[i][j] == '<')
			{
				token = ft_substr(lexer[i], j, 1);

				lexer[i] = ft_strdup(token);
				free(token);
			}
			j++;
		}
		i++;
	}
}

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
				var = ft_substr(lexer[i], j + 1, ft_strlen(lexer[i]));
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

char	**ft_lexer(char *input)
{
	char	**lexer;

	lexer = ft_split_lexer(input, ' ');
	ft_extend_var(lexer);
	return (lexer);
}