/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfree_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 02:37:04 by wescande          #+#    #+#             */
/*   Updated: 2017/03/23 00:31:18 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pfree_list(t_process *p)
{
	ft_ld_del(&p->data.d_for.token, &ft_tabdel);
	btree_del(&p->data.d_for.content, &ast_free);
	sleep(5);
	return (0);
}
