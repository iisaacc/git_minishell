/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:36:48 by isporras          #+#    #+#             */
/*   Updated: 2024/02/19 15:54:04 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_refresh_log(char *log)
{
	char	buffer[1024];
	char	*aux;

	aux = ft_strjoin_nofree(getenv("USER"), "@minishell ~");
	aux = ft_strjoin(aux, getcwd(buffer, sizeof(buffer)));
	aux = ft_strjoin(aux, "> ");
	log = aux;
	free(aux);
	return (log);
}
