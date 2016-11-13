#include "exec.h"

t_exec	g_exec[] =
{
	{TK_SEMI, &exec_semi},
	{TK_PIPE, &exec_pipe},
	{0, 0},
};

int		ft_exec(t_btree *ast)
{
	t_astnode	*item;
	int			i;

	i = 0;
	item = ast->item;
	if(!ast)
		return (0);
	while (g_exec[i].type)
	{
		if (item->type == g_exec[i].type)
		{
			(*g_exec[i].f)(ast);
			return (0);
		}
		i++;
	}
	return (0);
}
