/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:13:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/18 16:32:15 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_subtypes(t_lexer *aux, int *flag, int *file)
{
	if (aux->word[0] == '|')
		*flag = 1;
	if ((aux->word[0] == '>' || aux->word[0] == '<') && aux->word[1] != '<')
		*file = 1;
	aux->type = TOKEN;
	
} 

void	ft_types(t_lexer **lexer)
{
	t_lexer *aux;
	int flag; //flag para saver quando tem um pipe
	int file;
	
	file = 0;
	flag = 1;
	aux = *lexer;
	while (aux)
	{
		if (flag == 1)
		{
			aux->type = CMND;//es una funcion
			flag--;
		}
		else if (aux->word[0] == '-')//es una flag
			aux->type = FLAG;
		else if (aux->word[0] == '|' || aux->word[0] == '<' || aux->word[0] == '>')//es um token
			ft_subtypes(aux, &flag, &file);
		else if (file == 1)
		{
			aux->type = FILE;
			file--;
		}
		else	
			aux->type = STRING;
		aux = aux->next;
	}
}