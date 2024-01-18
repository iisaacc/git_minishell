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

char const	*ft_check_quotes(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			if(s[i] == '\0')
				return (NULL);
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"' && s[i] != '\0')
				i++;
			if(s[i] == '\0')
				return (NULL);
		}
		i++;
	}
	return (s);
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
	tmp = ft_calloc(ft_strlen(lexer[*i]) - ft_strlen(var) + 2 + ft_strlen(value), 1);
	ft_strlcpy(tmp, lexer[*i], *j + 1);
	if (value)
		tmp = ft_strjoin(tmp, value);
	else
		tmp = ft_strjoin(tmp, ft_strdup(""));
	tmp = ft_strjoin(tmp, &lexer[*i][*j + ft_strlen(var) + 1]);
	free(lexer[*i]);
	lexer[*i] = tmp;
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