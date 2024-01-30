/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:42:14 by isporras          #+#    #+#             */
/*   Updated: 2024/01/30 14:48:48 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_child_process(t_mini *aux)
{
	dup2(aux->infile, STDIN_FILENO);//Cambiamos el standar input por el fd de entrada deseado
	if (aux->infile != 0)//Asegurarse de que no estás cerrando la entrada estándar original
		close(aux->infile);
	dup2(aux->outfile, STDOUT_FILENO);
	if (aux->next != NULL) //Cerramos el fd de entrada del siguiente nodo
		close ((aux->next)->infile);
	if (ft_builtins(aux->envp, aux) == 0) //Si no es un builtin, ejecutamos el comando
	{
		execve(aux->full_path, aux->full_cmd, NULL);
		perror("execve:");
		exit(EXIT_FAILURE);
	}
}
int	ft_init_data_exec(t_mini **mini, t_exec **exec)
{
	if (!*exec)
		return 1;
	(*exec)->aux = *mini;
	if (!(*exec)->aux)
		return 1;
	(*exec)->total_cmnds = (*exec)->aux->total_cmnds;
	(*exec)->tmpin = dup(STDIN_FILENO);
	(*exec)->tmpout = dup(STDOUT_FILENO);
	return 0;
}

void	ft_close_restore(t_exec *exec)
{
	dup2(exec->tmpin, STDIN_FILENO);
	close(exec->tmpin);
	dup2(exec->tmpout, STDOUT_FILENO);
	close(exec->tmpout);
}

void	ft_executer(t_mini **mini)
{
	t_exec	*exec;
	int		i;

	exec = malloc(sizeof(t_exec));
	if (ft_init_data_exec(mini, &exec) == 1) //Inicializamos los datos necesarios para la función en una estructura
		return ;
	i = 0;
	while (i < exec->total_cmnds)
	{
		if (exec->total_cmnds > 1 && i < exec->total_cmnds - 1)
		{
			pipe(exec->fdpipe);
			(exec->aux->next)->infile = exec->fdpipe[0];
			exec->aux->outfile = exec->fdpipe[1];
		}
		exec->pid = fork();
		if (exec->pid == 0)
			ft_child_process(exec->aux);
		else if (exec->pid < 0)
			ft_perror("fork");
		else
		{
			if (i < exec->total_cmnds - 1)
				close(exec->aux->outfile);
			if (exec->aux->next == NULL)
				close(exec->aux->infile);
			waitpid(exec->pid, NULL, 0);
		}
		i++;
		exec->aux = exec->aux->next;
	}
	ft_close_restore(exec);
}

// void	ft_pipes(t_mini **mini)
// {
// 	int		fds[2];
// 	int		total_commands;
// 	int		i;
// 	t_mini	*aux;

// 	aux = *mini;
// 	if (!aux)
// 		return ;
// 	total_commands = aux->total_cmnds;
// 	if (total_commands < 2)
// 		return ;
// 	i = 0;
// 	while (i < total_commands - 1)
// 	{
// 		if (pipe(fds) == -1) {
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		aux->outfile = fds[1];
// 		if (aux->next)
// 		{
// 			(aux->next)->infile = fds[0];
// 			aux = aux->next;
// 		}
// 		i++;
// 	}
// }
