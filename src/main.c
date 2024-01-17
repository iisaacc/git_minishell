/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 14:55:30 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_list(t_lexer *lexer)
{
	int x;

	x = 0;
	while (lexer != NULL)
	{
		printf("%s\n", lexer->word);
		printf("%d\n", lexer->id);
		printf("%d\n", lexer->type);
		lexer = lexer->next;
		x++;
	}
}

int	main(int argc, char **argv)
{
	char *input;
	//char **split;
	t_lexer *lexer;
	argv = 0;

	lexer = NULL;
	if (argc > 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		create_nodes(&lexer, ft_lexer(input));
		ft_print_list(lexer);
	}
	int x;
	x = 0;
	clear_history();
}