/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_pathsolver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alao <alao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 18:21:54 by alao              #+#    #+#             */
/*   Updated: 2017/03/16 08:50:38 by alao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
** Solve the tilde pattern in the path
*/

static char		*tilde(t_comp *c, char *cmd)
{
	char		*t_home;
	char		*t_sub;
	char		*rt;
	int			l_cmd;

	t_home = NULL;
	t_sub = NULL;
	rt = NULL;
	l_cmd = ft_strlen(cmd);
	if ((t_home = ft_strdup(c->home)))
		if ((t_sub = ft_strsub(cmd, 1, (l_cmd - 1))))
			rt = ft_strjoin(t_home, t_sub);
	t_home ? ft_memdel((void *)&t_home) : (0);
	t_sub ? ft_memdel((void *)&t_sub) : (0);
	return (rt);
}

/*
** Advanced dots purge if the first is not enough. Remove a /path/ from
** the raw command if .. is found. Delete the . .
*/

static char		*dots_purge(char **scwd, char **scmd, int i)
{
	char		*tmp;
	char		*rt;
	int			j;

	tmp = NULL;
	rt = NULL;
	((j = ft_sstrlen(scwd)) > 0) ? (j--) : (0);
	(!(scwd[1])) ? (scwd[0] = ft_strdup("/")) : (0);
	while (scmd[i] && scwd[0])
	{
		if (!(ft_strcmp(scmd[i], ".")) || !(ft_strcmp(scmd[i], scwd[j])) ||
				!(ft_strcmp(scmd[i], "..")))
			(!(ft_strcmp(scmd[i], ".."))) ? (ft_memdel((void *)&scwd[j])) : (0);
		else if ((scwd[j + 1] = ft_strdup(scmd[i])))
			scwd[j + 2] = NULL;
		i++;
		((j = ft_sstrlen(scwd)) > 0) ? (j--) : (0);
		(!(scwd[0])) ? (scwd[0] = ft_strdup("/")) : (0);
	}
	rt = ft_sstrtostr(scwd, "/");
	tmp = ft_strjoin("/", rt);
	tmp ? ft_memdel((void *)&rt) : (0);
	rt = ft_strsub(tmp, 0, (ft_strlen(tmp) - 1));
	tmp ? ft_memdel((void *)&tmp) : (0);
	return (rt);
}

/*
** Solve the dots pattern in the path
*/

static char		*dots(char *cmd, char *cwd, int i)
{
	char		*tmp;
	char		**scmd;
	char		**scwd;

	tmp = NULL;
	if (!(ft_strcmp(cmd, ".")) || !(ft_strcmp(cmd, "./")))
		return (ft_strdup(cwd));
	if (!ft_strcmp(cmd, "..") && cwd && (i = ft_strlen(cwd)))
	{
		while (cwd[i] != '/')
			i--;
		(i) ? (tmp = ft_strncpy(ft_strnew(i), cwd, i)) : (0);
	}
	if (!tmp && cwd && (i = ft_strlen(cwd)))
	{
		scmd = ft_strsplit(cmd, '/');
		scwd = ft_strsplit(cwd, '/');
		tmp = dots_purge(scwd, scmd, 0);
		scmd ? ft_sstrfree(scmd) : (0);
		scwd ? ft_sstrfree(scwd) : (0);
	}
	if (!cwd)
		tmp = ft_strdup("/");
	return (tmp);
}

/*
** Path solving function. Turn any abstract path to the full version.
*/

char			*path_solver(t_comp *c, char *cmd, char *cwd)
{
	char		*dir;
	char		*tmp;
	char		*ncmd;

	dir = NULL;
	tmp = NULL;
	ncmd = (cmd != NULL) ? ft_strtrim(cmd) : NULL;
	cwd = getcwd(cwd, 512);
	!cwd ? cwd = ft_strdup(c->pwd) : (0);
	if (!ncmd || (*ncmd != '.' && *ncmd != '~' && *ncmd != '/'))
	{
		tmp = ft_strjoin(cwd, "/");
		dir = ncmd ? ft_strjoin(tmp, ncmd) : ft_strdup(cwd);
		tmp ? ft_memdel((void *)&tmp) : (0);
	}
	else
	{
		(*ncmd == '~') ? (dir = tilde(c, ncmd)) : (0);
		(*ncmd == '.') ? (dir = dots(ncmd, cwd, 0)) : (0);
		(*ncmd == '/') ? (dir = ft_strdup(ncmd)) : (0);
	}
	cwd ? ft_memdel((void *)&cwd) : (0);
	ncmd ? ft_memdel((void *)&ncmd) : (0);
	return (dir);
}
