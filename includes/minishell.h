/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:07:44 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/21 18:09:39 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHELL_NAME		"minishell"

# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "types.h"
# include "lexer.h"
# include "parser.h"
# include "ft_readline.h"
# include "job_control.h"
# include "exec.h"
# include "builtin.h"
# include "glob.h"
# include "completion.h"
# include "hash.h"
/* # define malloc(x) NULL */

# define SH_MSG(s, ...)	"{red}%s: " s "{eoc}\n", g_argv[0], ##__VA_ARGS__
# define SH_ERR(s, ...)	ft_dprintf(STDERR, SH_MSG(s, ##__VA_ARGS__))

#ifndef DEBUG
# define DEBUG_MODE 0
#else
# define DEBUG_MODE 1
#endif

struct	s_data
{
	t_flag		opts;
	char		**av_data;
	char		*c_arg;
	int			fd;
	char		**env;
	int			argc;
	char		**argv;
	t_line		line;
	t_lexer		lexer;
	t_parser	parser;
	t_comp		*comp;
	t_exec		exec;
	t_jobc		jobc;
	char		**local_var;
	t_list		*lst_func;
};

int		shell_init(int ac, char **av);
void	shell_exit(void);
int		data_init(int ac, char **av);
void	data_exit(void);
int		get_c_arg(char ***av, t_data *data);

void		content_free(void *data, size_t content_size);

char	*ft_putast(void *node);
void	ft_putast2(void *node);

#endif
