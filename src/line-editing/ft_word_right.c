/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:44:37 by jhalford          #+#    #+#             */
/*   Updated: 2016/11/10 13:44:37 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		ft_word_right(t_data *data, t_dlist **input_chain, char *buf)
{
	ft_cursor_right(data, input_chain, buf);
	while (!FT_WS(*(char *)(*input_chain)->content))
	{
		if (!ft_cursor_right(data, input_chain, buf))
			return (0);
	}
	while (FT_WS(*(char *)(*input_chain)->content))
	{
		if (!ft_cursor_right(data, input_chain, buf))
			return (0) ;
	}
	ft_cursor_left(data, input_chain, buf);
	return (0);
}
