/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/16 13:57:25 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	char *input;
	
	argv = 0;
	
	if (argc > 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		lexer(input);
		printf("%s\n", input);
		//rl_replace_line(" ", 0);
	}
	clear_history();
}