/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_getprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:07:30 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/20 15:18:52 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*job_getprocess(pid_t pid)
{
	t_jobc		*jobc;
	t_job		*j;
	t_list		*lst;
	t_list		*jlist;

	jobc = &data_singleton()->jobc;
	jlist = jobc->first_job;
	while (jlist)
	{
		j = jlist->content;
		if ((lst = ft_lst_find(j->first_process, &pid, &process_cmp_pid)))
			return (lst);
		jlist = jlist->next;
	}
	return (NULL);
}
