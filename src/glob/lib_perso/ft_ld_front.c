/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:26:11 by wescande          #+#    #+#             */
/*   Updated: 2017/03/21 18:32:33 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

t_ld	*ft_ld_front(t_ld *ld)
{
	if (ld)
		while (ld->prev)
			ld = ld->prev;
	return (ld);
}
