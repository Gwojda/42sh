/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 11:32:18 by gwojda            #+#    #+#             */
/*   Updated: 2017/02/19 12:01:37 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_hash_str(char *str)
{
	int i;
	int id;

	i = 0;
	id = 0;
	while (str[i])
	{
		id += str[i] * ft_pow(10, i);
		id = id % MAX_HASH;
		++i;
	}
	if (id < 0)
	{
		id *= -1;
		id = id % MAX_HASH;
	}
	ft_printf("id = %d\n", id);
	return (id);
}
