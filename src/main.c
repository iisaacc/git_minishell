/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/31 12:14:31 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_mini_lst(t_mini **mini)
{
	t_mini	*tmp;

	tmp = *mini;
	while (tmp != NULL)
	{
		printf("cmd:\n");
		ft_print_split(tmp->full_cmd);
		printf("total cmds: %d\n", tmp->total_cmnds);
		printf("id: %d\n", tmp->id);
		printf("path: %s\n", tmp->full_path);
		printf("infile fd: %d\n", tmp->infile);
		printf("outfile fd: %d\n\n", tmp->outfile);
		tmp = tmp->next;
	}
}

void ft_print_list(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		printf("word: %s\n", tmp->word);
		printf("id: %d\n", tmp->id);
		printf("type: %d\n\n", tmp->type);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	*lexer;
	t_mini	*mini;
	t_envp	*envp_list;

	envp_list = NULL;
	lexer = NULL;
	mini = NULL;
	if (argc > 1 && argv)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))//lee la línea
	{
		if (ft_check_quotes(input) == 1)//checkea si hay comillas sin cerrar
			return (EXIT_FAILURE);
		add_history(input);//si esta vacio no adiciona
		ft_init_var(envp, &envp_list);
		ft_lexer(&lexer, input);
		if (ft_parser(&lexer, &mini, envp, &envp_list) == 0)
			ft_executer(&mini);
		ft_print_list(&lexer);
		ft_print_mini_lst(&mini);
		ft_free_lsts(&lexer, &mini, &envp_list);
	}
	clear_history();
}

//MAIN DEBUG
// int	main(int argc, char **argv, char **envp)
// {
// 	t_lexer	*lexer;
// 	t_mini	*mini;
// 	t_envp	*envp_list;

// 	envp_list = NULL;
// 	lexer = NULL;
// 	mini = NULL;
// 	char	*str = ft_strdup("ls -l | cat -e | lo | wc -l >outfilee");
// 	if (!argv && !argc)
// 		return (1);
// 	ft_init_var(envp, &envp_list);
//	ft_lexer(&lexer, str);
//	if (ft_parser(&lexer, &mini, envp, &envp_list) == 0)
//		ft_executer(&mini);
// 	ft_print_list(&lexer);
// 	ft_print_mini_lst(&mini);
// 	ft_free_lsts(&lexer, &mini, &envp_list);
// 	return (0);
// }
