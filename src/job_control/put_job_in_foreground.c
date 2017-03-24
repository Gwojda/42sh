/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_foreground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:58:36 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/24 17:24:24 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		put_job_in_foreground(t_job *j, int cont)
{
	t_jobc	*jobc;

	jobc = &data_singleton()->jobc;
	if (SH_IS_INTERACTIVE(data_singleton()->opts))
		tcsetpgrp(STDIN, j->pgid);
	if (cont)
		tcsetattr(STDIN, TCSADRAIN, &j->tmodes);
	job_wait(j->id);
	if (SH_IS_INTERACTIVE(data_singleton()->opts))
	{
		tcsetpgrp(STDIN, jobc->shell_pgid);
		tcgetattr(STDIN, &j->tmodes);
		tcsetattr(STDIN, TCSADRAIN, &jobc->shell_tmodes);
	}
	job_remove(j->id);
	return (0);
}
