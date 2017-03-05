/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:40:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/05 15:42:31 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_instruction(int fd)
{
	t_list		*token;
	t_list		*ltoken;
	t_lexer		lexer;
	t_parser	parser;
	t_btree		*ast;
	char		*str;
	int			ret;

	lexer_init(&lexer);
	parser_init(&parser);
	token = NULL;
	ast = NULL;
	while (1)
	{
		if ((ret = readline(fd, get_lexer_stack(lexer) ||
			parser.state == UNDEFINED, &str)))
		{
			if (ret == -1)
				return (-1);
			return (parser.state == UNDEFINED ? error_EOF(&token,
			&parser, &ast) : 1);
		}
		ft_strappend(&lexer.str, str);
		if (get_lexer_stack(lexer) == BACKSLASH)
			pop(&lexer.stack);
		else if (get_lexer_stack(lexer) == DLESS)
			lexer.state = DLESS;
		ltoken = ft_lstlast(token);
		if (lexer_lex(token ? &ltoken : &token, &lexer))
			return (1);
		if (get_lexer_stack(lexer) > 1)
			continue ;
		lexer.state = DEFAULT;
		token_print(token);
		if (get_reserved_words(&token))
			return (1);
		if (insert_newline(&token))
			return (1);
		if (ft_parse(&ast, &token, &parser))
			continue ;
		if (parser.state == SUCCESS)
			break ;
		else if (parser.state == ERROR && SH_IS_INTERACTIVE(data_singleton()->opts))
			return (error_syntax(&token, &parser, &ast));
		else if (parser.state == ERROR)
			error_syntax(&token, &parser, &ast);
	}
	DG("Before execution:");
	btree_print(STDBUG, ast, &ft_putast);
	if (ft_exec(&ast))
		return (1);
	instruction_free(&token, &parser, &ast);
	ft_add_str_in_history(lexer.str);
	return (0);
}

int		get_input_fd()
{
	t_data	*data;
	char	*file;
	int		fds[2];
	int		fd;

	data = data_singleton();
	fd = STDIN;
	if (SH_IS_INTERACTIVE(data->opts))
		return (fd);
	else if (data->opts & SH_OPTS_LC)
	{
		pipe(fds);
		fd = fds[PIPE_READ];
		file = shell_get_avdata();
		write(fds[PIPE_WRITE], file, ft_strlen(file));
		close(fds[PIPE_WRITE]);
		fcntl(fd, F_SETFD, FD_CLOEXEC);
		return (fd);
	}
	else if ((file = shell_get_avdata()))
	{
		if ((fd = open(file, O_RDONLY | O_CLOEXEC)) < 0)
			return (-1);
		return (fd);
	}
	else
		return (STDIN);
}

int		main(int ac, char **av)
{
	int		fd;

	setlocale(LC_ALL, "");
	shell_init(ac, av);
	if ((fd = get_input_fd()) < 0)
	{
		ft_printf("{red}%s: %s: No such file or directory\n{eoc}", SHELL_NAME, shell_get_avdata());
		return (1);
	}
	DG("{inv}{bol}{gre}start of shell{eoc} JOBC is %s, fd=[%i]",
			SH_HAS_JOBC(data_singleton()->opts)?"ON":"OFF", fd);
	while (handle_instruction(fd) == 0)
	{
//		lexer_clean;
//		parser_clean;
		;
	}
	shell_exit();
	return (0);
}
