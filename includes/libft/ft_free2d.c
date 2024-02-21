/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:46:48 by isporras          #+#    #+#             */
/*   Updated: 2024/02/21 15:41:36 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i] != NULL)
		{
			//printf("STR = %s\n", str[i]);
			//printf("I = %d\n", i);
			free(str[i]);
			i++;
		}
		free(str);
	}
}
