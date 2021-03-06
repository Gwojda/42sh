/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plaunch_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:53:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/27 16:46:06 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		error_launch(char *error_ori, char *error_type, int error_code)
{
	SH_ERR("%s%s", error_ori, error_type);
	exit(error_code);
}

int				plaunch_file(t_process *p)
{
	if (!p->data.cmd.path)
		error_launch("command not found: ", p->data.cmd.av[0], 127);
	else if (access(p->data.cmd.path, F_OK) == -1)
		error_launch(p->data.cmd.av[0], ": no such file or directory", 127);
	else if (S_ISDIR(p->data.cmd.stat->st_mode))
		error_launch(p->data.cmd.av[0], ": is a directory", 126);
	else if (access(p->data.cmd.path, X_OK) == -1)
		error_launch("permission denied: ", p->data.cmd.av[0], 126);
	shell_fds_destroy();
	execve(p->data.cmd.path,
			p->data.cmd.av,
			data_singleton()->env);
	error_launch("internal execve error on ", p->data.cmd.av[0], 42);
	return (0);
}
