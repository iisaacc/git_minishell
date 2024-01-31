/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:49 by isporras          #+#    #+#             */
/*   Updated: 2024/01/31 14:13:43 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_remove_quotes(char **str_lexer)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = 0;
	while (str_lexer[i])
	{
		new_str = ft_strdup("");
		while (str_lexer[i][j] != '\0')
		{
			if (str_lexer[i][j] == '\'' || str_lexer[i][j] == '\"')
			{
				if (str_lexer[i][j] == '\'')
				{
					j++;
					while (str_lexer[i][j] != '\'')
						new_str = ft_strjoin(new_str, ft_substr(&str_lexer[i][j++], 0 , 1));
					j++;
				}
				else if (str_lexer[i][j] == '\"')
				{
					j++;
					while (str_lexer[i][j] != '\"')
						new_str = ft_strjoin(new_str, ft_substr(&str_lexer[i][j++], 0 , 1));
					j++;
				}
			}
			new_str = ft_strjoin(new_str, ft_substr(&str_lexer[i][j++], 0 , 1));
		}
		free(str_lexer[i]);
		str_lexer[i] = new_str;
		i++;
	}
	return (str_lexer);
}

void	ft_quotes_input(char **input)
{
	char	*new_input;
	char	*prompt;

	while (ft_check_quotes(*input) > 0)
	{
		if (ft_check_quotes(*input) == 1)
			prompt = "quotes>";
		else
			prompt = "dquotes>";
		new_input = readline(prompt);
		if (new_input)
			*input = ft_strjoin(*input, new_input);
	}
}

int	ft_check_quotes(char const *s)
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
				return (1);
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"' && s[i] != '\0')
				i++;
			if(s[i] == '\0')
				return (2);
		}
		i++;
	}
	return (0);
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

//Extiende la variable global $ siempre que no esté entre comillas simples
void	ft_extend_var(char **lexer)
{
	int	i;
	int	j;
	int	q;

	q = 0;
	i = 0;
	while (lexer[i])
	{
		j = 0;
		while (lexer[i][j])
		{
			if (lexer[i][j] == '\'' && q == 0)
				q = 1;
			else if (lexer[i][j] == '\'' && q == 1)
				q = 0;
			if (lexer[i][j] == '$' && q == 0)
				ft_put_var(lexer, &i, &j);
			j++;
		}
		i++;
	}
}

char	**ft_lexer(t_lexer **lst_lexer, char *input)
{
	char	**str_lexer;
	if (!input)
		return (NULL);
	str_lexer = ft_split_lexer(input, ' ');
	ft_extend_var(str_lexer);
	str_lexer = ft_get_tokens(str_lexer);
	//str_lexer = ft_remove_quotes(str_lexer);
	create_nodes(lst_lexer, str_lexer);
	free(input);//free del input
	return (str_lexer);
}