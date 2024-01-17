/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 14:08:06 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_list(t_lexer *lexer)
{
	int x; 

	x = 0;
	while (lexer->next != NULL)
	{
		printf("%s\n", lexer->word);
		printf("%d\n", lexer->id);
		lexer = lexer->next;
		x++;	
	}
}

int	main(int argc, char **argv)
{
	char *input;
	char **split;
	t_lexer *lexer;

	lexer = NULL;
	if (argc > 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		ast(&lexer, ft_lexer(input));
		ft_print_list(lexer);
	}
	int x;
	x = 0;
	ast(&lexer, argv);
	while (lexer->next != NULL)
	{
		printf("%s\n", lexer->word);
		printf("%d\n", lexer->id);
		lexer = lexer->next;
		x++;	
	}
	clear_history();
}