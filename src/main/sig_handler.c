#include "minishell.h"
pid_t	g_pid;

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_pid)
			kill(g_pid, SIGINT);
	}
}