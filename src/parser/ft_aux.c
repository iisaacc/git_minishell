/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:05 by isporras          #+#    #+#             */
/*   Updated: 2024/02/13 16:55:05 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_check_bad_input(t_lexer **lexer)
{
	t_lexer	*aux;
	int pipe;

	pipe = 0;
	aux = *lexer;
	while (aux)
	{
		if (aux->type == PIPE)
			pipe++;
		if (aux->type == LESS)
		{
			if (open((aux->next)->word, O_RDONLY) == -1)
			{
				ft_file_error(-1, (aux->next)->word);
				ft_delete_pipe(lexer, pipe);
				aux = *lexer;
			}
		}
		if (aux)
			aux = aux->next;
	}
}

void	ft_delete_pipe(t_lexer **lexer, int pipe)
{
	t_lexer	*aux;
	int		lap;
	int		i;

	lap = 0;
	aux = *lexer;
	i = 0;
	while (aux)
	{
		if (aux->type == PIPE && lap == pipe)
		{
			ft_delete_node(lexer, i);
			lap++;
		}
		if (lap == pipe)
			ft_delete_node(lexer, i);
		aux = aux->next;
		i++;
	}
}
