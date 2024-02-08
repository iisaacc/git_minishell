/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/08 14:59:02 by isporras         ###   ########.fr       */
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

void	ft_print_list(t_lexer **lexer)
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

void	final_free(char *input, char *log, t_envp **envp)
{
	ft_free_envp_list(envp);//hay que quedar fuera del bucle
	free(log);
	free(input);
}

//int	main(int argc, char **argv, char **envp)
//{
//	char	*input;
//	t_lexer	*lexer;
//	t_mini	*mini;
//	t_envp	*envp_list;
//	char	*log;
//	int		last_status;

//	envp_list = NULL;
//	lexer = NULL;
//	mini = NULL;
//	last_status = 0;
//	if (argc > 1 && argv)
//	{
//		printf("Wrong number of arguments\n");
//		return (1);
//	}
//	ft_init_var(envp, &envp_list);
//	log = ft_refresh_log();
//	//singal_init();
//	while ((input = readline(log)))//lee la línea
//	{
//		ft_quotes_input(&input);//devuelve el control al usuario si hay comillas sin cerrar
//		if (ft_strncmp(input, "\0", 1) != 0)//si esta vacio no adiciona al historial
//			add_history(input);
//		if (ft_lexer(&lexer, input, last_status) != NULL)//crea la lista de tokens
//		{
//			last_status = ft_parser(&lexer, &mini, envp, &envp_list);//los builtins se ejecutan en el parser
//			if (last_status == -1)
//				last_status = ft_executer(&mini);
//		}
//		//printf("last status: %d\n", last_status);
//		ft_print_list(&lexer);
//		ft_print_mini_lst(&mini);
//		ft_free_lsts(&lexer, &mini, log);
//		log = ft_refresh_log();
//	}
//	final_free(input, log, &envp_list);
//	clear_history();
//}

//MAIN DEBUG
 int	main(int argc, char **argv, char **envp)
 {
 	t_lexer	*lexer;
 	t_mini	*mini;
 	t_envp	*envp_list;
 	int		last_status;

 	envp_list = NULL;
 	lexer = NULL;
 	mini = NULL;
 	last_status = 0;
 	char	*input = ft_strdup("ls>>outfile");
 	if (!argv && !argc)
 		return (1);
 	ft_init_var(envp, &envp_list);
 	ft_quotes_input(&input);
 	if (ft_lexer(&lexer, input, last_status) != NULL)//crea la lista de tokens
 	{
 		ft_print_list(&lexer);
 		last_status = ft_parser(&lexer, &mini, envp, &envp_list);//los builtins se ejecutan en el parser
 		if (last_status == -1)
 			last_status = ft_executer(&mini);
 	}
 	ft_print_mini_lst(&mini);
 	//ft_free_lsts(&lexer, &mini);
 	return (0);
 }
