/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:42:14 by isporras          #+#    #+#             */
/*   Updated: 2024/02/17 15:17:03 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_close_wait(t_exec *exec, int i)
{
	int	status;

	if (i < exec->total_cmnds - 1)
		close(exec->aux->outfile);//Cerramos el fd de escritura si no estamos en el ultimo comando para que el siguiente reciba el EOF
	if (exec->aux->next == NULL)
		close(exec->aux->infile);
	waitpid(exec->pid, &status, 0);
	if (WIFEXITED(status))//Comprueba si el proceso hijo terminó normalmente
		return (WEXITSTATUS(status));
	else
		return (1);//Si no terminó normalmente, devolvemos 1
	return (0);
}

void	ft_set_next_pipe(t_exec *exec)
{
	if (exec->total_cmnds > 1)
	{
		pipe(exec->fdpipe);
		if (exec->aux->next && (exec->aux->next)->infile == STDIN_FILENO)
			(exec->aux->next)->infile = exec->fdpipe[0];
		if (exec->aux->outfile == STDOUT_FILENO)
			exec->aux->outfile = exec->fdpipe[1];
	}
}

void	ft_child_process(t_mini *aux)
{
	dup2(aux->infile, STDIN_FILENO);//Cambiamos el standar input por el fd de entrada deseado
	if (aux->infile != 0)//Asegurarse de que no estás cerrando la entrada estándar original
		close(aux->infile);
	dup2(aux->outfile, STDOUT_FILENO);
	if (aux->next != NULL) //Cerramos el fd de entrada del siguiente nodo
		close ((aux->next)->infile);
	if (ft_is_builtin(aux->full_cmd[0]) == 1)
	{
		ft_builtins(aux->envp, aux);
		exit(last_status);
	}
	else if (execve(aux->full_path, aux->full_cmd, NULL) == -1)
	{
		ft_perror(aux->full_path);
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

int	ft_executer(t_mini **mini)
{
	t_exec	*exec;
	int		i;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (1);
	if (ft_init_data_exec(mini, &exec) == 1) //Inicializamos los datos necesarios para la función en una estructura
		return (last_status); //error
	i = 0;
	while (exec->aux && i < exec->total_cmnds)
	{
		if (exec->total_cmnds > 1 && i < exec->total_cmnds - 1)
			ft_set_next_pipe(exec);//Si hay más de un comando, establecemos el siguiente pipe
		if ((exec->aux->full_cmd && ft_is_parent(exec->aux->full_cmd[0]) == 0 && ft_is_builtin(exec->aux->full_cmd[0]) == 1)//cd se ejecuta en el proceso padre
			|| (exec->aux->full_path && ft_is_builtin(exec->aux->full_cmd[0]) == 0))
		{
			exec->pid = fork();
			if (exec->pid == 0)
				ft_child_process(exec->aux);
			else if (exec->pid < 0)
				ft_perror("fork");
			else
				last_status = ft_close_wait(exec, i);
		}
		else if (exec->aux->full_cmd && ft_is_parent(exec->aux->full_cmd[0]) != 0)
			ft_bt_parent(exec->aux, exec->aux->envp);
		i++;
		exec->aux = exec->aux->next;
	}
	ft_close_restore(exec);
	free(exec);
	return (last_status);
}
