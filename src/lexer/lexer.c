/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:49 by isporras          #+#    #+#             */
/*   Updated: 2024/01/17 18:09:14 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_add_token(char **src, int y, char *token)
{
	int		i;
	int		x;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 2));
	i = 0;
	x = 0;
	while (src[i])
	{
		if (x == y)
		{
			dst[x++] = token;
			if (src[i][0] == *token)
				dst[x++] = ft_substr(src[i], 1, ft_strlen(&src[i][1]));
			else
				dst[x++] = ft_substr(src[i], 0, ft_strlen(src[i]) - 1);
			i++;
		}
		else
			dst[x++] = ft_strdup(src[i++]);
	}
	dst[x] = NULL;
	return (dst);
}

char	**ft_get_tokens(char **lexer)
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
			if ((lexer[i][j] == '>' || lexer[i][j] == '<')
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
	return (lexer);
}

void	ft_put_var(char **lexer, int *i, int *j)
{
	char	*var;
	char	*value;
	char	*tmp;
	int		len;

	len = 0;
	while (lexer[*i][*j + 1 + len] && lexer[*i][*j + 1 + len] != ' ' && lexer[*i][*j + 1 + len] != '\"')
		len++;
	var = ft_substr(lexer[*i], *j + 1, len);
	value = getenv(var);
	if (value)
	{
		tmp = ft_calloc(ft_strlen(lexer[*i]) - ft_strlen(var) + 2 + ft_strlen(value), 1);
		ft_strlcpy(tmp, lexer[*i], *j + 1);
		tmp = ft_strjoin(tmp, value);
		tmp = ft_strjoin(tmp, &lexer[*i][*j + ft_strlen(var) + 1]);
		lexer[*i] = tmp;
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
	lexer = ft_get_tokens(lexer);
	return (lexer);
}