#include "minishell.h"

void	ft_format_vars(char **av, char **env)
{
	while (*av)
	{
		if (**av == '$')
			*av = ft_env_getval(env, *av + 1);
		av++;
	}
}
