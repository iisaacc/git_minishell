/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:42:14 by isporras          #+#    #+#             */
/*   Updated: 2024/01/25 15:36:05 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_fork_execve(t_mini **mini)
{
	int		pid;
	t_mini	*aux;
	int		total_cmnds;
	int		i;

	aux = *mini;
	total_cmnds = aux->total_cmnds;
	i = 0;
	while (i < total_cmnds)
	{
		pid = fork();
		if (pid == -1)
		{
			//ft_clean;
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (dup2(aux->infile, STDIN_FILENO) < 0 || dup2(aux->outfile, STDOUT_FILENO) < 0)//Hace dup2 a los pipes
			{
				perror("dup2:");
				exit(EXIT_FAILURE);
			}
			if(execve(aux->full_path, (*mini)->full_cmd, NULL) == -1)//Ejecuta comandos
			{
				perror("execve:");
				exit(EXIT_FAILURE);
			}
			close(aux->infile);
			close(aux->outfile);
			if (dup2(STDIN_FILENO, aux->infile) < 0 || dup2(STDOUT_FILENO, aux->outfile) < 0) //Restaurar in/out
			{
				perror("dup2:");
				exit(EXIT_FAILURE);
			}
		}
		i++;
		aux = aux->next;
	}
}

void	ft_pipes(t_mini **mini)
{
	int		fds[2];
	int		total_commands;
	int		i;
	t_mini	*aux;

	aux = *mini;
	if (!aux)
		return ;
	total_commands = aux->total_cmnds;
	if (total_commands < 2)
		return ;
	i = 0;
	while (i < total_commands - 1)
	{
		pipe(fds);
		aux->outfile = fds[1];
		(aux->next)->infile = fds[0];
		aux = aux->next;
		i++;
	}
}

// void	ft_example_redirections(t_mini **mini)
// {
// 	//guardar in/out
// 	t_redir	redir;
// 	int	i;

// 	redir.tmpin = dup(0);
// 	redir.tmpout = dup(1);
// 	i = 0;
// 	while (i < numsimplecommands)
// 	{
// 		dup2(mini->infile, 0);//redirijir input
// 		close(redir.fdin);
// 		if (i == numsimplecommands1) // Último comando
// 		{
// 			if(outfile)
// 				redir.fdout = open(mini->outfile);
// 			else
// 				redir.fdout = dup(redir.tmpout);
// 		}
// 		else //Demás comandos
// 		{
// 			pipe(redir.fdpipe);
// 			redir.fdout = redir.fdpipe[1];
// 			redir.fdin = redir.fdpipe[0];
// 		}
// 		dup2(redir.fdout, 1);// Redirijir output
// 		close(redir.fdout);
// 		redir.fork = fork();// Crear proceso hijo
// 		if(redir.fork == 0)
// 		{
// 			execvp(mini->full_cmd[i][0], mini->full_cmd[i][1]);
// 			perror("execvp:");
// 			exit(1);
// 		}
// 		i++;
// 	}
// 	dup2(redir.tmpin, 0);//Restaurar in/out
// 	dup2(redir.tmpout, 1);
// 	close(redir.tmpin);
// 	close(redir.tmpout);
// 	if (!background)// Esperar al último comando
// 		waitpid(redir.fork, NULL)
// }
