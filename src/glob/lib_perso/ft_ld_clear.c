/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 19:56:49 by wescande          #+#    #+#             */
/*   Updated: 2017/03/21 18:41:08 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ld_clear(t_ld **ld, void (*del)())
{
	if (!ld || !*ld)
		return ;
	*ld = ft_ld_front(*ld);
	while (*ld)
	{
		ft_ld_del(ld, del);
	}
}
