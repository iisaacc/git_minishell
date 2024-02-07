/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:55:30 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/07 14:44:24 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sigint(int sig)
{
	sig = 0;
	printf("entrou\n");
	ft_putstr_fd("\n", 2);
	rl_redisplay();//fuerza atualizacion de la linea
	rl_on_new_line();//se comunica con las funciones para decir que hay una nueva linea
	rl_replace_line("", 0);
}

int singal_init()
{
	signal(SIGINT, ft_sigint);
	return (0);
}