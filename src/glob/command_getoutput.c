/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_getoutput.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 19:44:25 by wescande          #+#    #+#             */
/*   Updated: 2017/03/24 14:47:25 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define BUF_SIZE	1024

static char		*manage_output(int *fds)
{
	int			ret;
	char		buf[BUF_SIZE + 1];
	char		*output;

	output = NULL;
	close(fds[PIPE_WRITE]);
	while ((ret = read(fds[PIPE_READ], buf, BUF_SIZE)) > 0)
	{
		buf[ret] = 0;
		ft_strappend(&output, buf);
	}
	close(fds[PIPE_READ]);
	return (output);
}

char			*command_getoutput(char *command)
{
	int			ret;
	int			pid;
	int			fds[2];
	char		**av;

	if (!command)
		return (NULL);
	pipe(fds);
	if (!(pid = process_fork(NULL)))
	{
		close(fds[PIPE_READ]);
		dup2_close(fds[PIPE_WRITE], STDOUT);
		av = ft_sstradd(NULL, data_singleton()->binary);
		av = ft_sstradd(av, "-c");
		av = ft_sstradd(av, command);
		execve(data_singleton()->binary, av, data_singleton()->env);
		exit(1);
	}
	waitpid(pid, &ret, WUNTRACED);
	return (manage_output(fds));
}

char			*get_output(char *command)
{
	char	*output;
	int		len;

	if (!(output = command_getoutput(command)))
		return (NULL);
	len = ft_strlen(output);
	while (len && output[--len] == '\n')
		output[len] = '\0';
	return (output);
}
