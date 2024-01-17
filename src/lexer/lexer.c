/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:49 by isporras          #+#    #+#             */
/*   Updated: 2024/01/17 17:14:24 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_get_tokens(char **lexer)
{
	int		i;
	int		j;
	char	*token;
	//char	**tmp;

	i = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if ((lexer[i][j] == '>' || lexer[i][j] == '<' || lexer[i][j] == '|')
				&& (ft_strlen(lexer[i]) != 1) && (j == 0 || j == ft_strlen(lexer[i])))
			{
				token = ft_substr(lexer[i], j, 1);
				if (j == 0)
					tmp = ft_add_token(lexer, i, token);
				else
					tmp = ft_add_token(lexer, i + 1, token);
				//ft_free_2d(lexer);
				lexer = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_put_var(char **lexer, int *i, int *j)
{
	char	*var;
	char	*value;
	int		len;

	len = 0;
	while (lexer[*i][*j + len] && lexer[*i][*j + len] != ' ')
		len++;
	var = ft_substr(lexer[*i], *j + 1, len);
	value = getenv(var);
	if (value)
	{
		len = 0;
		while (len < ft_strlen(value))
		{
			free(lexer[*i]);
			lexer[*i] = ft_strdup(value);
		}
	}
	free(var);
}

void	ft_put_var(char **lexer, int *i, int *j)
{
	char	*var;
	char	*value;
	int		len;

	len = 0;
	while (lexer[*i][*j + len] && lexer[*i][*j + len] != ' ')
		len++;
	var = ft_substr(lexer[*i], *j + 1, len);
	value = getenv(var);
	if (value)
	{
		len = 0;
		while (len < ft_strlen(value))
		{
			free(lexer[*i]);
			lexer[*i] = ft_strdup(value);
		}
	}
	free(var);
}

void	ft_extend_var(char **lexer)
{
	int		i;
	int		j;

	i = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if (lexer[i][j] == '$')
				ft_put_var(lexer, &i, &j);
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