/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 18:07:35 by isporras         ###   ########.fr       */
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

int	main()
{
	char *input = "echo \"hhh $HOM ffff\" \"hello      there\" $USER how are \'you \'doing?  \"  |wc  \" -l >outfile";
	ft_print_split(ft_lexer(input));
	//create_nodes(&lexer, ft_lexer(input));
	//ft_print_list(lexer);

	//lexer = NULL;
	//if (argc > 1 && argv)
	//{
	//	printf("Wrong number of arguments\n");
	//	return (1);
	//}
	//while((input = readline("Minishell>")))
	//{
	//	add_history(input);
	//	create_nodes(&lexer, ft_lexer(input));
	//	//ft_print_split(ft_lexer(input));
	//	ft_types(lexer);
	//	ft_print_list(lexer);
	//}
	//clear_history();
}