/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfree_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:18:34 by ariard            #+#    #+#             */
/*   Updated: 2017/03/21 20:53:45 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pfree_func(t_process *p)
{
	ft_putstr("hello");
	btree_del(&p->data.function.content, &ast_free);
	return (0);
}
