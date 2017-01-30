/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ampersand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:01:30 by jhalford          #+#    #+#             */
/*   Updated: 2017/01/30 21:11:38 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		exec_ampersand(t_btree **ast)
{
	t_process	*p;

	if (SHELL_HAS_JOBC(data_singleton()->opts))
		data_singleton()->exec.job.attributes |= JOB_BG;
	ft_exec(&(*ast)->left);
	if (SHELL_HAS_JOBC(data_singleton()->opts))
		data_singleton()->exec.job.attributes &= ~JOB_BG;
	ft_exec(&(*ast)->right);

	p = &data_singleton()->exec.process;	
	if (!(p->script & SCRIPT_LOOP))
		btree_delone(ast, &ast_free);
	return (0);
}
