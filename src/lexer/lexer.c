/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:49 by isporras          #+#    #+#             */
/*   Updated: 2024/02/09 09:30:17 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (ft_strncmp(&lexer[*i][*j], "$?", 3) == 0)
		value = ft_itoa(last_status);
	else
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
	ft_remove_quotes(str_lexer);
	ft_print_split(str_lexer);
	str_lexer = ft_check_syntax(str_lexer); //Chequea errores sintacticos como un < o > o << o >> al final de la línea
	ft_print_split(str_lexer);
	create_nodes(lst_lexer, str_lexer);
	free(input);//free del input
	return (str_lexer);
}
