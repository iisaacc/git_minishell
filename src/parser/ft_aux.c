/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:05 by isporras          #+#    #+#             */
/*   Updated: 2024/02/19 18:20:41 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_broken_pipe(t_lexer **lexer, int pipe)
{
	t_lexer	*aux;
	int		lap;
	int		i;

	lap = 0;
	aux = *lexer;
	i = 0;
	while (aux)
	{
		if (aux->type == PIPE)
			lap++;
		if (lap == pipe)
			aux->broken = 1;
		aux = aux->next;
	}
}

//void	ft_refresh_id(t_lexer **lexer)
//{
//	t_lexer	*aux;
//	int		lap;

//	lap = 0;
//	aux = *lexer;
//	while (aux)
//	{
//		aux->id = lap;
//		lap++;
//		aux = aux->next;
//	}
//}

//t_lexer	*ft_delete_node(t_lexer **lexer, int x)
//{
//	t_lexer	*aux;
//	t_lexer	*prev;
//	int		i;

//	i = 0;
//	aux = *lexer;
//	prev = NULL;
//	while (aux)
//	{
//		if (x == aux->id)
//		{
//			if (prev)
//				prev->next = aux->next;
//			else if (aux->next)
//				*lexer = aux->next;
//			else
//				*lexer = NULL;
//			free(aux->word);
//			free(aux);
//			if (prev && prev->next)
//				return (ft_refresh_id(lexer), prev->next);
//			else
//				return (ft_refresh_id(lexer), *lexer);
//		}
//		else
//		{
//			prev = aux;
//			aux = aux->next;
//			i++;
//		}
//	}
//	return (NULL);
//}

void	ft_check_bad_input(t_lexer **lexer)
{
	t_lexer	*aux;
	int		pipe;

	pipe = 0;
	aux = *lexer;
	while (aux)
	{
		if (aux->type == PIPE)
			pipe++;
		if (aux->type == LESS || aux->type == GREATER)
		{
			if (aux->broken == 0 && ((aux->type == LESS && open((aux->next)->word, O_RDONLY) == -1)
				|| (aux->type == GREATER && open((aux->next)->word, O_WRONLY
						| O_CREAT | O_TRUNC, 0644) == -1)))
			{
				ft_perror_mod((aux->next)->word, strerror(errno), 1);
				ft_broken_pipe(lexer, pipe);
			}
		}
		if (aux)
			aux = aux->next;
	}
}



//t_lexer	*ft_delete_pipe(t_lexer **lexer, int pipe)
//{
//	t_lexer	*aux;
//	int		lap;
//	int		i;
//	int		p;

//	lap = 0;
//	aux = *lexer;
//	i = 0;
//	p = 0;
//	while (aux)
//	{
//		if (aux->type == PIPE)
//			lap++;
//		if (lap == pipe)
//		{
//			if (aux->type == PIPE)
//				p = 1;
//			aux = ft_delete_node(lexer, i);
//			while (aux && aux->type != PIPE)
//				aux = ft_delete_node(lexer, i);
//			if (aux && aux->type == PIPE && p == 0)
//				aux = ft_delete_node(lexer, i);
//			return (aux);
//		}
//		if (aux)
//			aux = aux->next;
//		i++;
//	}
//	return (NULL);
//}
