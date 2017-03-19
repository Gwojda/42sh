/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:04:03 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/18 00:51:40 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	job_notify_change(int id)
{
	t_job		*job;
	t_jobc		*jobc;

	jobc = &data_singleton()->jobc;
	job = ft_lst_find(jobc->first_job, &id, job_cmp_id)->content;
//	if (job->attrs & JOB_BG) utilise pour notif dynamic
		job_format(job, JOBS_OPTS_L);
}