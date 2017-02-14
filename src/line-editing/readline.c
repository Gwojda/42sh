/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:19:48 by gwojda            #+#    #+#             */
/*   Updated: 2017/02/14 15:17:33 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_init_line(void)
{
	data_singleton()->line.input = NULL;
	data_singleton()->line.copy_tmp = NULL;
	data_singleton()->line.pos = 0;
	data_singleton()->line.prompt_size = 0;
	data_singleton()->line.list_size = 0;
	data_singleton()->line.list_end = NULL;
	data_singleton()->line.list_beg = NULL;
	data_singleton()->line.opt = 0;
}

void			ft_init_history(void)
{
	int		fd;
	char	*str;

	fd = open(".42sh_history", O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &str) > 0)
	{
		ft_push_back_history(&data_singleton()->line.list_beg,
		ft_create_history_list(str));
		free(str);
	}
	free(str);
	close(fd);
}

struct termios	*ft_save_termios(int save)
{
	static struct termios	*term_save = NULL;

	if (save)
	{
		term_save = (struct termios *)malloc(sizeof(struct termios));
		tcgetattr(0, term_save);
	}
	return (term_save);
}

void	ft_init_termios(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
}

void	readline_init(char *prompt)
{
	static int	beg = 0;

	if (!beg)
	{
		ft_init_line();
		ft_init_history();
		beg = 1;
	}
	ft_save_termios(1);
	ft_init_termios();
	if (STR)
		ft_strdel(&STR);
	data_singleton()->line.list_cur = data_singleton()->line.list_beg;
	POS = 0;
	prompt ? ft_putstr(prompt) : ft_prompt();
}

char	*readline(char *prompt)
{
	char	*input;

	readline_init(prompt);
	input = ft_read_stdin();
	ft_putchar('\n');
	if (!prompt)
		input = ft_history_parsing();
	if (tcsetattr(0, TCSANOW, ft_save_termios(0)) == -1)
		return (NULL);
	return (input);
}
