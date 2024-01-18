/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/18 17:18:46 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_list(t_lexer *lexer)
{
	int x;
	t_lexer *aux;
	
	aux = lexer;
	x = 0;
	while (aux != NULL)
	{
		printf("%s %d %d\n", aux->word, aux->id, aux->type);
		aux = aux->next;
		x++;
	}
}

int	main(int argc, char **argv)//
{
/* 	char *input = "echo \"hhh $HOME ffff\" \"hello      there\" $USER how are \'you \'doing?  \"  |wc  \" -l >outfile";
	t_lexer *lexer;

	lexer = NULL;
	//ft_print_split(ft_lexer(input));
	create_nodes(&lexer, ft_lexer(input));
	ft_print_list(lexer);
	ft_free_2d(&input);
	free_node(&lexer); */
	char *input;
	t_lexer *lexer;
	
	lexer = NULL;
	if (argc > 1 && argv)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		create_nodes(&lexer, ft_lexer(input));
		//ft_print_split(ft_lexer(input));
		ft_types(lexer);
		ft_print_list(lexer);
	}
	clear_history();
}