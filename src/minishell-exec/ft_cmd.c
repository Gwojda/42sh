#include "minishell.h"
extern pid_t	g_pid;

int		ft_cmd_process(char **argv, char ***env_p)
{
	char	**path;
	char	*execpath;

	path = ft_strsplit(ft_getenv(*env_p, "PATH"), ':');
	ft_expand_dollar(argv, *env_p);
	if (ft_builtin(argv, env_p))
		return (0);
	else if (ft_strchr(argv[0], '/'))
		execpath = argv[0];
	else if (!(execpath = ft_findexec(path, argv[0])))
	{
		ft_printf("minishell: command not found: %s\n", argv[0]);
		return (-1);
	}
	return (ft_cmd_exec(execpath, argv, env_p));
}

int		ft_cmd_exec(char *execpath, char **argv, char ***env_p)
{
	pid_t	pid;
	int		status;
	char	**environ;
	char	**sstr;

	sstr = NULL;
	if (access(execpath, X_OK) == -1)
	{
		ft_printf("minishell: permission denied: %s\n", argv[0]);
		return (-1);
	}
	if ((pid = fork()) == -1)
		return (-1);
	else if (pid == 0)
	{
		environ = ft_sstrdup(*env_p);
		execve(execpath, argv, environ);
	}
	else
	{
		g_pid = pid;
		wait(&status);
		sstr = ft_sstradd(sstr, "?");
		sstr = ft_sstradd(sstr, ft_itoa(status));
		builtin_setenv(sstr, env_p);
	}
	return (0);
}

char	**ft_cmd_getav(char *cmd)
{
	return (ft_split_whitespaces(cmd));
}