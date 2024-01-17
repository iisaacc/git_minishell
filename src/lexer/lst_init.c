/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:35:16 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 14:51:00 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_lexer **node)
{
	t_lexer	*node_aux;

	if (!node | !*node)
		return ;
	while (*node)
	{
		node_aux = (*node)->next;
		free((*node)->word);
		free(*node);
		*node = node_aux;
	}
	*node = NULL;
}

t_lexer	*last_list(t_lexer *lst)//va hasta el final de la lista
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	add_new(t_lexer **lst, t_lexer *new)//añande un nodo a la lista
{
	t_lexer	*aux;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = last_list(*lst);
	aux->next = new;
}

t_lexer *create_new(char *input, int x)
{
	t_lexer *node;
	
	node = NULL;
	node = malloc(sizeof(t_lexer));
	node->word = ft_substr(input, 0, ft_strlen(input));
	node->next = NULL;
	node->type = 0;
	node->id = x + 1;
	return (node);
}

void create_nodes(t_lexer **lexer, char **input)//crea todos los nudos
{
	int x;
	
	x = 0;
	if(*lexer)
		free_node(lexer);
	while (input[x])
	{
		add_new(lexer, create_new(input[x], x));
		x++;
	}
}
