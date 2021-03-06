/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pset_if.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:19:50 by wescande          #+#    #+#             */
/*   Updated: 2017/03/20 16:26:35 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pset_if(t_process *p, t_btree *ast)
{
	p->data.d_if.content = btree_map(ast->right, &node_copy);
	p->type = PROCESS_IF;
	return (0);
}
